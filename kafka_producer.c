/*
 * librdkafka - Apache Kafka C library
 *
 * Copyright (c) 2017, Magnus Edenhill
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/**
 * Simple Apache Kafka producer using the Kafka driver from librdkafka
 * (https://github.com/edenhill/librdkafka)
 */

#include <stdio.h>
#include <signal.h>
#include <string.h>
#include "kafka_aurora.h"

static volatile sig_atomic_t run = 1;

/**
 * @brief Signal termination of program
 */
static void stop(int sig) {
    run = 0;
//        fclose(stdin); /* abort fgets() */
}

/**
 * @brief Message delivery report callback.
 *
 * This callback is called exactly once per message, indicating if
 * the message was succesfully delivered
 * (rkmessage->err == RD_KAFKA_RESP_ERR_NO_ERROR) or permanently
 * failed delivery (rkmessage->err != RD_KAFKA_RESP_ERR_NO_ERROR).
 *
 * The callback is triggered from rd_kafka_poll() and executes on
 * the application's thread.
 */
static void
dr_msg_cb(rd_kafka_t *rk, const rd_kafka_message_t *rkmessage, void *opaque) {
    if (rkmessage->err)
        fprintf(stderr, "%% Message delivery failed: %s\n",
                rd_kafka_err2str(rkmessage->err));
//	else
//		fprintf(stderr,
//				"%% Message delivered (%zd bytes,  partition %" PRId32 ")\n",
//				rkmessage->len, rkmessage->partition);
    /* The rkmessage is destroyed automatically by librdkafka */
}

rd_kafka_t* init_producer(kafka_params *kap){
    rd_kafka_t *rk;
    rd_kafka_conf_t *conf;
    char errstr[512];
    const char *brokers = kap->brokers;

    /* 创建一个kafka配置占位 */
    conf = rd_kafka_conf_new();
    /*创建broker集群*/
    if (rd_kafka_conf_set(conf, "bootstrap.servers", brokers, errstr,
                          sizeof(errstr)) != RD_KAFKA_CONF_OK) {
        fprintf(stderr, "%s\n", errstr);
        return NULL;
    }

    /*设置发送报告回调函数，rd_kafka_produce()接收的每条消息都会调用一次该回调函数
     *应用程序需要定期调用rd_kafka_poll()来服务排队的发送报告回调函数*/
    rd_kafka_conf_set_dr_msg_cb(conf, dr_msg_cb);

    /*创建producer实例
      rd_kafka_new()获取conf对象的所有权,应用程序在此调用之后不得再次引用它*/
    rk = rd_kafka_new(RD_KAFKA_PRODUCER, conf, errstr, sizeof(errstr));
    if (!rk) {
        fprintf(stderr, "%% Failed to create new producer:%s\n", errstr);
        return NULL;
    }

    return rk;
}

int au_kafka_producer(rd_kafka_t* rk, kafka_params *kap, const char *key, const char *value) {

    const char *topic = kap->topic;
    rd_kafka_resp_err_t err;
    retry:
    /*Send/Produce message.
      这是一个异步调用，在成功的情况下，只会将消息排入内部producer队列， 对broker的实际传递尝试由后台线程处理，之前注册的传递回调函数(dr_msg_cb)
      用于在消息传递成功或失败时向应用程序发回信号*/
    err = rd_kafka_producev(
            /* producer handle */
            rk,
            /* topic name */
            RD_KAFKA_V_TOPIC(topic),
            /*生成payload的副本*/
            RD_KAFKA_V_MSGFLAGS(RD_KAFKA_MSG_F_COPY),
            /*消息体和长度*/
            RD_KAFKA_V_VALUE((char*)value, strlen(value)),
            //key length
            RD_KAFKA_V_KEY(key, strlen(key)),
            /*可选键及其长度*/
            RD_KAFKA_V_OPAQUE(NULL),
            RD_KAFKA_V_END);
    if(err){
        fprintf(stderr,
                "%% Failed to produce to topic %s: %s\n", topic, rd_kafka_err2str(err));
        if (err == RD_KAFKA_RESP_ERR__QUEUE_FULL) {
            /*如果内部队列满，等待消息传输完成并retry, 内部队列表示要发送的消息和已发送或失败的消息，
            内部队列受限于queue.buffering.max.messages配置项*/
            rd_kafka_poll(rk, 1000);
            goto retry;
        }
    } else {
//			fprintf(stderr, "%% Enqueued message (%zd bytes) for topic %s\n", strlen(value), topic);
    }

    /*producer应用程序应不断地通过以频繁的间隔调用rd_kafka_poll()来为 传送报告队列提供服务。在没有生成消息以确定先前生成的消息已发送了其
    发送报告回调函数(和其他注册过的回调函数)期间，要确保rd_kafka_poll() 仍然被调用*/
    rd_kafka_poll(rk, 0);

    return 0;
}

void destroy_producer(rd_kafka_t* rk){

//	fprintf(stderr, "%% Flushing final message.. \n");
    /*rd_kafka_flush是rd_kafka_poll()的抽象化， 等待所有未完成的produce请求完成，通常在销毁producer实例前完成
    以确保所有排列中和正在传输的produce请求在销毁前完成*/
    rd_kafka_flush(rk, 10 * 1000);

    if (rd_kafka_outq_len(rk) > 0)
        fprintf(stderr, "%% %d message(s) were not delivered\n", rd_kafka_outq_len(rk));
    /* Destroy the producer instance */
    rd_kafka_destroy(rk);
}
