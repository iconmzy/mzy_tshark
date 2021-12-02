#include "jsonopt.h"

void PrintDataParts(struct PartHead *partHead)
{
	for (int i = 0; i < partHead->partsNum; i++)
	{
//		printf("\nname:%s\n", partHead->dataParts[i].name);
//		printf("length:%d\n", partHead->dataParts[i].length);
//		printf("abbName:%s\n", partHead->dataParts[i].abbName);
		int typeTemp = partHead->dataParts[i].type;
//		printf("type:%d\n", typeTemp);
		if (typeTemp == 999)
		{
			PrintDataParts(partHead->dataParts[i].partHead);
		}
	}
}
void PrintExProtocol(struct exProtocol *exproto)
{
    int i = 0;
	printf("\nprotocolName:%s\n", exproto->protocolName);
	printf("shortName:%s\n", exproto->shortName);
	printf("filterName:%s\n", exproto->filterName);
	while (exproto->port[i] != 0 && i <10){
        printf("port:%d\n", exproto->port[i]);
        i++;
	}

	printf("transportProtocol:%s\n", exproto->transportProtocol);
	//printf("totalLength:%d\n", exproto->totalLength);
	PrintDataParts(exproto->partHead);
}

int ReadPart(JsonReader *reader, PartHead **partHead)
{
	//read parts
	// printf("\nRead from parts\n");
	if (!json_reader_read_member(reader, "parts"))
	{
		printf("Read parts Error\n");
		return 0;
	}
	else
	{
		int partsNum = json_reader_count_elements(reader);
		*partHead = (struct PartHead *)malloc(sizeof(struct PartHead));
		// printf("partsNum:%d\n", partsNum);
		(*partHead)->partsNum = partsNum;
		int readNum = 0;
		(*partHead)->dataParts = (struct parts *)malloc(partsNum * sizeof(struct parts));
		while (readNum < partsNum)
		{
			gboolean readFlag;
			// printf("\nreadNum:%d\n", readNum);
			readFlag = json_reader_read_element(reader, readNum);
			if (!readFlag)
			{
				printf("Read Element Error\n");
			}
			readFlag = json_reader_read_member(reader, "name");
			if (!readFlag)
			{
				printf("Read name Error\n");
			}
			strcpy((*partHead)->dataParts[readNum].name, json_reader_get_string_value(reader));
			// printf("name:%s\n", json_reader_get_string_value(reader));
			json_reader_end_member(reader);

			readFlag = json_reader_read_member(reader, "abbName");
			if (!readFlag)
			{
				printf("Read abbName Error\n");
			}
			strcpy((*partHead)->dataParts[readNum].abbName, json_reader_get_string_value(reader));
			// printf("abbName:%s\n", json_reader_get_string_value(reader));
			json_reader_end_member(reader);

			readFlag = json_reader_read_member(reader, "length");
			if (!readFlag)
			{
				printf("Read length Error\n");
			}
			(*partHead)->dataParts[readNum].length = json_reader_get_int_value(reader);
			// printf("length:%d\n", json_reader_get_int_value(reader));
			json_reader_end_member(reader);

			readFlag = json_reader_read_member(reader, "type");
			if (!readFlag)
			{
				printf("Read type Error\n");
			}
			int typeTemp = json_reader_get_int_value(reader);
			(*partHead)->dataParts[readNum].type = typeTemp;
			 //printf("type:%d\n", typeTemp);
			json_reader_end_member(reader);

			if (typeTemp == 999)
			{
				ReadPart(reader, &((*partHead)->dataParts[readNum].partHead));
			}
			else
			{
				(*partHead)->dataParts[readNum].partHead = NULL;
			}
			json_reader_end_element(reader);
			readNum++;
		}
	}
	json_reader_end_member(reader);
}

int ReadHead(JsonReader *reader, exProtocol *proto)
{

	//read protocolName
	if (!json_reader_read_member(reader, "protocolName"))
	{
		printf("Read protocolName Error\n");
		return 0;
	}
	else
	{
		strcpy(proto->protocolName, json_reader_get_string_value(reader));
		json_reader_end_member(reader);
	}
	//read transportProtocol
	if (!json_reader_read_member(reader, "transportProtocol"))
	{
		printf("Read transportProtocol Error\n");
		return 0;
	}
	else
	{
		strcpy(proto->transportProtocol, json_reader_get_string_value(reader));
		json_reader_end_member(reader);
	}
	//read port
    int readNum = 0;
    int portsNum = 0;
	if (!json_reader_read_member(reader, "ports"))
	{
		printf("Read port Error\n");
		return 0;
	}
	else
	{

         portsNum = json_reader_count_elements(reader);

        while (readNum < 10 & readNum < portsNum  ){
            gboolean readFlag;
            //printf("\nreadNum:%d\n", readNum);
            readFlag = json_reader_read_element(reader, readNum);
            if (!readFlag)
            {
                printf("Read ports Element Error\n");
            }
            proto->port[readNum] = json_reader_get_int_value(reader);

            readNum++;
            json_reader_end_element(reader);

        }

        json_reader_end_member(reader);

	}

	//read totalLength
/*
	if (!json_reader_read_member(reader, "totalLength"))
	{
		printf("Read totalLength Error\n");
		return 0;
	}
	else
	{
		proto->totalLength = json_reader_get_int_value(reader);
		json_reader_end_member(reader);
	}
*/

	//read shortName
	if (!json_reader_read_member(reader, "shortName"))
	{
		printf("Read shortName Error\n");
		return 0;
	}
	else
	{
		strcpy(proto->shortName, json_reader_get_string_value(reader));
		json_reader_end_member(reader);
	}

	//read filterName
	if (!json_reader_read_member(reader, "filterName"))
	{
		printf("Read filterName Error\n");
		return 0;
	}
	else
	{
		strcpy(proto->filterName, json_reader_get_string_value(reader));
		json_reader_end_member(reader);
	}
	return 1;
}
int ParseJson(char *filePath, struct exProtocol *proto)
{
	printf("start json\n");
	JsonParser *parser;
	GError *error;
	// char filename[] = "/home/xia/桌面/tcpsample/json/test2.json";
	parser = json_parser_new();
	error = NULL;
	gboolean loadflag = json_parser_load_from_file(parser, filePath, &error);
	if (error)
	{
		g_print("Unable to parse '%s':%s\n", filePath, error->message);
		g_error_free(error);
		g_object_unref(parser);
		return EXIT_FAILURE;
	}
	if (!loadflag)
	{
		g_print("Unable to parse '%s'\n", filePath);
	}
	JsonReader *reader = json_reader_new(json_parser_get_root(parser));
	ReadHead(reader, proto);
	ReadPart(reader, &proto->partHead);
	PrintExProtocol(proto);

	g_object_unref(reader);
	g_object_unref(parser);

	return EXIT_SUCCESS;
}

int ParseAllJson(char *dirPath, allExProtocols *protos)
{
	DIR *dirp;
	struct dirent *direntp;
	dirp = opendir(dirPath);
	int pathLen = strlen(dirPath) + 50;
	char *filePath = (char *)malloc(pathLen);
	int i = 0;
	while ((direntp = readdir(dirp)) != NULL)
	{
		if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
		{
			continue;
		}
		memset(filePath, 0, pathLen);
		strcpy(filePath, dirPath);
		strcat(filePath, "/");
		strcat(filePath, direntp->d_name);
//		printf("Find Json:%s\n", filePath);
		ParseJson(filePath, &protos->exProto[i]);
		i++;
		if (i > protos->exProtocolNum)
			return -1;
	}
	return 1;
}
int CountJsonFile(char *dirPath)
{
	DIR *dirp;
	struct dirent *direntp;
	dirp = opendir(dirPath);
	if(dirp == NULL){
	    printf("新增协议JSON路径错误！\n");
	    _exit(-1);
	}
	int num = 0;
	while ((direntp = readdir(dirp)) != NULL)
	{
		if (!strcmp(direntp->d_name, ".") || !strcmp(direntp->d_name, ".."))
		{
			continue;
		}
		num++;
	}
	return num;
}