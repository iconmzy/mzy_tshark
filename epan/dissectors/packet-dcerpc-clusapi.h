/* DO NOT EDIT
	This file was automatically generated by Pidl
	from clusapi.idl and clusapi.cnf.

	Pidl is a perl based IDL compiler for DCE/RPC idl files.
	It is maintained by the Samba team, not the Wireshark team.
	Instructions on how to download and install Pidl can be
	found at https://gitlab.com/wireshark/wireshark/-/wikis/Pidl
*/

#include "packet-dcerpc-winreg.h"
#include "packet-dcerpc-misc.h"

#ifndef __PACKET_DCERPC_CLUSAPI_H
#define __PACKET_DCERPC_CLUSAPI_H

int clusapi_dissect_struct_RPC_SECURITY_DESCRIPTOR(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_RPC_SECURITY_ATTRIBUTES(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_CLUSTER_OPERATIONAL_VERSION_INFO(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_IDL_CLUSTER_SET_PASSWORD_STATUS(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define IDL_CLUSTER_SET_PASSWORD_IGNORE_DOWN_NODES (1)
extern const value_string clusapi_IDL_CLUSTER_SET_PASSWORD_FLAGS_vals[];
int clusapi_dissect_enum_IDL_CLUSTER_SET_PASSWORD_FLAGS(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
int clusapi_dissect_struct_CLUSTER_CREATE_GROUP_INFO_RPC(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_bitmap_ClusterEnumType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_ENUM_ENTRY(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_ENUM_LIST(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_GROUP_ENUM_ENTRY(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_RESOURCE_ENUM_ENTRY(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_GROUP_ENUM_LIST(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_RESOURCE_ENUM_LIST(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define CLUSTER_RESOURCE_DEFAULT_MONITOR (0x00000000)
#define CLUSTER_RESOURCE_SEPARATE_MONITOR (0x00000001)
extern const value_string clusapi_clusapi_CreateResourceFlags_vals[];
int clusapi_dissect_enum_CreateResourceFlags(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define ClusterResourceInitializing (0x00000001)
#define ClusterResourceOnline (0x00000002)
#define ClusterResourceOffline (0x00000003)
#define ClusterResourceFailed (0x00000004)
#define ClusterResourceOnlinePending (0x00000081)
#define ClusterResourceOfflinePending (0x00000082)
#define ClusterResourceStateUnknown (0xFFFFFFFF)
extern const value_string clusapi_clusapi_ClusterResourceState_vals[];
int clusapi_dissect_enum_ClusterResourceState(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define ClusterGroupOnline (0x00000000)
#define ClusterGroupOffline (0x00000001)
#define ClusterGroupFailed (0x00000002)
#define ClusterGroupPartialOnline (0x00000003)
#define ClusterGroupPending (0x00000004)
#define ClusterGroupStateUnknown (0xFFFFFFFF)
extern const value_string clusapi_clusapi_ClusterGroupState_vals[];
int clusapi_dissect_enum_ClusterGroupState(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
int clusapi_dissect_bitmap_ClusterGroupEnumType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define ClusterNodeUp (0x00000000)
#define ClusterNodeDown (0x00000001)
#define ClusterNodePaused (0x00000002)
#define ClusterNodeJoining (0x00000003)
#define ClusterNodeStateUnknown (0xFFFFFFFF)
extern const value_string clusapi_clusapi_ClusterNodeState_vals[];
int clusapi_dissect_enum_ClusterNodeState(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define CLUS_RESCLASS_UNKNOWN (0x00000000)
#define CLUS_RESCLASS_STORAGE (0x00000001)
#define CLUS_RESCLASS_NETWORK (0x00000002)
extern const value_string clusapi_clusapi_ResourceClass_vals[];
int clusapi_dissect_enum_ResourceClass(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
int clusapi_dissect_struct_CLUS_RESOURCE_CLASS_INFO(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define CLUSCTL_RESOURCE_UNKNOWN (0x01000000)
#define CLUSCTL_RESOURCE_GET_CHARACTERISTICS (0x01000005)
#define CLUSCTL_RESOURCE_GET_FLAGS (0x01000009)
#define CLUSCTL_RESOURCE_GET_CLASS_INFO (0x0100000D)
#define CLUSCTL_RESOURCE_GET_REQUIRED_DEPENDENCIES (0x01000011)
#define CLUSCTL_RESOURCE_GET_NAME (0x01000029)
#define CLUSCTL_RESOURCE_GET_RESOURCE_TYPE (0x0100002D)
#define CLUSCTL_RESOURCE_GET_ID (0x01000039)
#define CLUSCTL_RESOURCE_ENUM_COMMON_PROPERTIES (0x01000051)
#define CLUSCTL_RESOURCE_GET_RO_COMMON_PROPERTIES (0x01000055)
#define CLUSCTL_RESOURCE_GET_COMMON_PROPERTIES (0x01000059)
#define CLUSCTL_RESOURCE_SET_COMMON_PROPERTIES (0x0140005E)
#define CLUSCTL_RESOURCE_VALIDATE_COMMON_PROPERTIES (0x01000061)
#define CLUSCTL_RESOURCE_GET_COMMON_PROPERTY_FMTS (0x01000065)
#define CLUSCTL_RESOURCE_ENUM_PRIVATE_PROPERTIES (0x01000079)
#define CLUSCTL_RESOURCE_GET_RO_PRIVATE_PROPERTIES (0x0100007D)
#define CLUSCTL_RESOURCE_GET_PRIVATE_PROPERTIES (0x01000081)
#define CLUSCTL_RESOURCE_SET_PRIVATE_PROPERTIES (0x01400086)
#define CLUSCTL_RESOURCE_VALIDATE_PRIVATE_PROPERTIES (0x01000089)
#define CLUSCTL_RESOURCE_GET_PRIVATE_PROPERTY_FMTS (0x0100008D)
#define CLUSCTL_RESOURCE_ADD_REGISTRY_CHECKPOINT (0x014000A2)
#define CLUSCTL_RESOURCE_DELETE_REGISTRY_CHECKPOINT (0x014000A6)
#define CLUSCTL_RESOURCE_GET_REGISTRY_CHECKPOINTS (0x010000A9)
#define CLUSCTL_RESOURCE_ADD_CRYPTO_CHECKPOINT (0x014000AE)
#define CLUSCTL_RESOURCE_DELETE_CRYPTO_CHECKPOINT (0x014000B2)
#define CLUSCTL_RESOURCE_GET_CRYPTO_CHECKPOINTS (0x010000B5)
#define CLUSCTL_RESOURCE_UPGRADE_DLL (0x014000BA)
#define CLUSCTL_RESOURCE_ADD_REGISTRY_CHECKPOINT_64BIT (0x014000BE)
#define CLUSCTL_RESOURCE_ADD_REGISTRY_CHECKPOINT_32BIT (0x014000C2)
#define CLUSCTL_RESOURCE_GET_NETWORK_NAME (0x01000169)
#define CLUSCTL_RESOURCE_NETNAME_REGISTER_DNS_RECORDS (0x01000172)
#define CLUSCTL_RESOURCE_GET_DNS_NAME (0x01000175)
#define CLUSCTL_RESOURCE_NETNAME_SET_PWD_INFO (0x0100017A)
#define CLUSCTL_RESOURCE_NETNAME_DELETE_CO (0x0100017E)
#define CLUSCTL_RESOURCE_NETNAME_VALIDATE_VCO (0x01000181)
#define CLUSCTL_RESOURCE_NETNAME_RESET_VCO (0x01000185)
#define CLUSCTL_RESOURCE_NETNAME_CREDS_UPDATED (0x01c0018a)
#define CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO (0x01000191)
#define CLUSCTL_RESOURCE_STORAGE_IS_PATH_VALID (0x01000199)
#define CLUSCTL_RESOURCE_IPADDRESS_RENEW_LEASE (0x014001BE)
#define CLUSCTL_RESOURCE_IPADDRESS_RELEASE_LEASE (0x014001C2)
#define CLUSCTL_RESOURCE_QUERY_MAINTENANCE_MODE (0x010001E1)
#define CLUSCTL_RESOURCE_SET_MAINTENANCE_MODE (0x014001E6)
#define CLUSCTL_RESOURCE_STORAGE_SET_DRIVELETTER (0x014001EA)
#define CLUSCTL_RESOURCE_STORAGE_GET_DISK_INFO_EX (0x010001F1)
#define CLUSCTL_RESOURCE_STORAGE_GET_DIRTY (0x01000219)
#define CLUSCTL_RESOURCE_STORAGE_GET_MOUNTPOINTS (0x01000211)
#define CLUSCTL_RESOURCE_STORAGE_GET_SHARED_VOLUME_INFO (0x01000225)
#define CLUSCTL_RESOURCE_VM_START_MIGRATION (0x01600004)
#define CLUSCTL_RESOURCE_VM_CANCEL_MIGRATION (0x01600008)
#define CLUSCTL_RESOURCE_SET_CSV_MAINTENANCE_MODE (0x01400296)
#define CLUSCTL_RESOURCE_ENABLE_SHARED_VOLUME_DIRECTIO (0x0140028a)
#define CLUSCTL_RESOURCE_DISABLE_SHARED_VOLUME_DIRECTIO (0x0140028e)
#define CLUSCTL_RESOURCE_SET_SHARED_VOLUME_BACKUP_MODE (0x0140029a)
#define CLUSCTL_RESOURCE_GET_RELATED_RESOURCE_NAMES (0x01001fad)
#define CLUSCTL_RESOURCE_POOL_GET_DRIVE_INFO (0x010002b5)
#define CLUSCTL_RESOURCE_CLOUD_WITNESS_UPDATE_TOKEN (0x014020e6)
#define CLUSCTL_RESOURCE_NETNAME_CHECK_OU_PERMISSIONS (0x07002121)
#define CLUSCTL_RESOURCE_NETNAME_CHECK_AD_STATE (0x07002125)
extern const value_string clusapi_clusapi_ResourceControlCode_vals[];
int clusapi_dissect_enum_ResourceControlCode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define CLUSCTL_RESOURCE_TYPE_UNKNOWN (0x02000000)
#define CLUSCTL_RESOURCE_TYPE_GET_CHARACTERISTICS (0x02000005)
#define CLUSCTL_RESOURCE_TYPE_GET_FLAGS (0x02000009)
#define CLUSCTL_RESOURCE_TYPE_GET_CLASS_INFO (0x0200000D)
#define CLUSCTL_RESOURCE_TYPE_GET_REQUIRED_DEPENDENCIES (0x02000011)
#define CLUSCTL_RESOURCE_TYPE_GET_ARB_TIMEOUT (0x02000015)
#define CLUSCTL_RESOURCE_TYPE_ENUM_COMMON_PROPERTIES (0x02000051)
#define CLUSCTL_RESOURCE_TYPE_GET_RO_COMMON_PROPERTIES (0x02000055)
#define CLUSCTL_RESOURCE_TYPE_GET_COMMON_PROPERTIES (0x02000059)
#define CLUSCTL_RESOURCE_TYPE_SET_COMMON_PROPERTIES (0x0240005E)
#define CLUSCTL_RESOURCE_TYPE_VALIDATE_COMMON_PROPERTIES (0x02000061)
#define CLUSCTL_RESOURCE_TYPE_GET_COMMON_PROPERTY_FMTS (0x02000065)
#define CLUSCTL_RESOURCE_TYPE_GET_COMMON_RESOURCE_PROPERTY_FMTS (0x02000069)
#define CLUSCTL_RESOURCE_TYPE_ENUM_PRIVATE_PROPERTIES (0x02000079)
#define CLUSCTL_RESOURCE_TYPE_GET_RO_PRIVATE_PROPERTIES (0x0200007D)
#define CLUSCTL_RESOURCE_TYPE_GET_PRIVATE_PROPERTIES (0x02000081)
#define CLUSCTL_RESOURCE_TYPE_SET_PRIVATE_PROPERTIES (0x02400086)
#define CLUSCTL_RESOURCE_TYPE_VALIDATE_PRIVATE_PROPERTIES (0x02000089)
#define CLUSCTL_RESOURCE_TYPE_GET_PRIVATE_PROPERTY_FMTS (0x0200008D)
#define CLUSCTL_RESOURCE_TYPE_GET_PRIVATE_RESOURCE_PROPERTY_FMTS (0x02000091)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_GET_AVAILABLE_DISKS (0x02000195)
#define CLUSCTL_RESOURCE_TYPE_NETNAME_VALIDATE_NETNAME (0x02000235)
#define CLUSCTL_RESOURCE_TYPE_VALIDATE_PATH (0x02000231)
#define CLUSCTL_RESOURCE_TYPE_GEN_APP_VALIDATE_DIRECTORY (0x02000239)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_GET_DRIVELETTERS (0x020001ED)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_GET_AVAILABLE_DISKS_EX (0x020001F5)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_REMAP_DRIVELETTER (0x02000201)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_GET_DISKID (0x02000205)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_IS_CLUSTERABLE (0x02000209)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_RELEASE_OWNERSHIP (0x0240020E)
#define CLUSCTL_RESOURCE_TYPE_STORAGE_IS_CSV_FILE (0x1000229)
#define CLUSCTL_RESOURCE_TYPE_CLOUD_WITNESS_VALIDATE_CREDENTIALS (0x020020e1)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_ELIGIBLE_LOGDISKS (0x02002149)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_ELIGIBLE_TARGET_DATADISKS (0x0200214D)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_ELIGIBLE_SOURCE_DATADISKS (0x02002151)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_REPLICA_VOLUMES (0x02002159)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_LOG_VOLUME (0x0200215D)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_REPLICATED_DISKS (0x02002155)
#define CLUSCTL_RESOURCE_TYPE_REPLICATION_GET_RESOURCE_GROUP (0x02002161)
extern const value_string clusapi_clusapi_ResourceTypeControlCode_vals[];
int clusapi_dissect_enum_ResourceTypeControlCode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define CLUSCTL_GROUP_UNKNOWN (0x03000000)
#define CLUSCTL_GROUP_GET_CHARACTERISTICS (0x03000005)
#define CLUSCTL_GROUP_GET_FLAGS (0x03000009)
#define CLUSCTL_GROUP_GET_NAME (0x03000029)
#define CLUSCTL_GROUP_GET_ID (0x03000039)
#define CLUSCTL_GROUP_ENUM_COMMON_PROPERTIES (0x03000051)
#define CLUSCTL_GROUP_GET_RO_COMMON_PROPERTIES (0x03000055)
#define CLUSCTL_GROUP_GET_COMMON_PROPERTIES (0x03000059)
#define CLUSCTL_GROUP_SET_COMMON_PROPERTIES (0x0340005E)
#define CLUSCTL_GROUP_VALIDATE_COMMON_PROPERTIES (0x03000061)
#define CLUSCTL_GROUP_GET_COMMON_PROPERTY_FMTS (0x03000065)
#define CLUSCTL_GROUP_ENUM_PRIVATE_PROPERTIES (0x03000079)
#define CLUSCTL_GROUP_GET_RO_PRIVATE_PROPERTIES (0x0300007D)
#define CLUSCTL_GROUP_GET_PRIVATE_PROPERTIES (0x03000081)
#define CLUSCTL_GROUP_SET_PRIVATE_PROPERTIES (0x03400086)
#define CLUSCTL_GROUP_VALIDATE_PRIVATE_PROPERTIES (0x03000089)
extern const value_string clusapi_clusapi_GroupControlCode_vals[];
int clusapi_dissect_enum_GroupControlCode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define CLUSCTL_NODE_UNKNOWN (0x04000000)
#define CLUSCTL_NODE_GET_CHARACTERISTICS (0x04000005)
#define CLUSCTL_NODE_GET_FLAGS (0x04000009)
#define CLUSCTL_NODE_GET_NAME (0x04000029)
#define CLUSCTL_NODE_GET_ID (0x04000039)
#define CLUSCTL_NODE_GET_CLUSTER_SERVICE_ACCOUNT_NAME (0x04000041)
#define CLUSCTL_NODE_ENUM_COMMON_PROPERTIES (0x04000051)
#define CLUSCTL_NODE_GET_RO_COMMON_PROPERTIES (0x04000055)
#define CLUSCTL_NODE_GET_COMMON_PROPERTIES (0x04000059)
#define CLUSCTL_NODE_SET_COMMON_PROPERTIES (0x0440005E)
#define CLUSCTL_NODE_VALIDATE_COMMON_PROPERTIES (0x04000061)
#define CLUSCTL_NODE_ENUM_PRIVATE_PROPERTIES (0x04000079)
#define CLUSCTL_NODE_GET_RO_PRIVATE_PROPERTIES (0x0400007D)
#define CLUSCTL_NODE_GET_PRIVATE_PROPERTIES (0x04000081)
#define CLUSCTL_NODE_SET_PRIVATE_PROPERTIES (0x04400086)
#define CLUSCTL_NODE_VALIDATE_PRIVATE_PROPERTIES (0x04000089)
extern const value_string clusapi_clusapi_NodeControlCode_vals[];
int clusapi_dissect_enum_NodeControlCode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define ClusterNetworkUnavailable (0x00000000)
#define ClusterNetworkDown (0x00000001)
#define ClusterNetworkPartitioned (0x00000002)
#define ClusterNetworkUp (0x00000003)
#define ClusterNetworkStateUnknown (0xFFFFFFFF)
extern const value_string clusapi_clusapi_ClusterNetworkState_vals[];
int clusapi_dissect_enum_ClusterNetworkState(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define ClusterNetInterfaceFailed (0x00000000)
#define ClusterNetInterfaceUnreachable (0x00000001)
#define ClusterNetInterfaceUnavailable (0x00000002)
#define ClusterNetInterfaceUp (0x00000003)
#define ClusterNetInterfaceStateUnknown (0xFFFFFFFF)
extern const value_string clusapi_clusapi_ClusterNetInterfaceState_vals[];
int clusapi_dissect_enum_ClusterNetInterfaceState(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
int clusapi_dissect_bitmap_ClusterResTypeEnumType(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define CLUSCTL_CLUSTER_UNKNOWN (0x07000000)
#define CLUSCTL_CLUSTER_GET_FQDN (0x0700003D)
#define CLUSCTL_CLUSTER_CHECK_VOTER_EVICT (0x07000045)
#define CLUSCTL_CLUSTER_CHECK_VOTER_DOWN (0x07000049)
#define CLUSCTL_CLUSTER_SHUTDOWN (0x0700004D)
#define CLUSCTL_CLUSTER_ENUM_COMMON_PROPERTIES (0x07000051)
#define CLUSCTL_CLUSTER_GET_RO_COMMON_PROPERTIES (0x07000055)
#define CLUSCTL_CLUSTER_GET_COMMON_PROPERTIES (0x07000059)
#define CLUSCTL_CLUSTER_SET_COMMON_PROPERTIES (0x0740005E)
#define CLUSCTL_CLUSTER_VALIDATE_COMMON_PROPERTIES (0x07000061)
#define CLUSCTL_CLUSTER_GET_COMMON_PROPERTY_FMTS (0x07000065)
#define CLUSCTL_CLUSTER_ENUM_PRIVATE_PROPERTIES (0x07000079)
#define CLUSCTL_CLUSTER_GET_RO_PRIVATE_PROPERTIES (0x0700007D)
#define CLUSCTL_CLUSTER_GET_PRIVATE_PROPERTIES (0x07000081)
#define CLUSCTL_CLUSTER_SET_PRIVATE_PROPERTIES (0x07400086)
#define CLUSCTL_CLUSTER_VALIDATE_PRIVATE_PROPERTIES (0x07000089)
#define CLUSCTL_CLUSTER_GET_SHARED_VOLUME_ID (0x07000291)
#define CLUSCTL_CLUSTER_UPGRADE_CLUSTER_VERSION (0x074000ce)
#define CLUSCTL_CLUSTER_CLEAR_UPGRADE_IN_PROGRESS (0x074000d2)
#define CLUSCTL_CLUSTER_IS_READY_FOR_UPGRADE (0x070000d5)
extern const value_string clusapi_clusapi_ClusterControlCode_vals[];
int clusapi_dissect_enum_ClusterControlCode(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
#define CLUSPROP_SYNTAX_ENDMARK (0x00000000)
#define CLUSPROP_SYNTAX_NAME (0x00040003)
#define CLUSPROP_SYNTAX_RESCLASS (0x00020002)
#define CLUSPROP_SYNTAX_LIST_VALUE_SZ (0x00010003)
#define CLUSPROP_SYNTAX_LIST_VALUE_EXPAND_SZ (0x00010004)
#define CLUSPROP_SYNTAX_LIST_VALUE_DWORD (0x00010002)
#define CLUSPROP_SYNTAX_LIST_VALUE_BINARY (0x00010001)
#define CLUSPROP_SYNTAX_LIST_VALUE_MULTI_SZ (0x00010005)
#define CLUSPROP_SYNTAX_LIST_VALUE_LONG (0x00010007)
#define CLUSPROP_SYNTAX_LIST_VALUE_EXPANDED_SZ (0x00010008)
#define CLUSPROP_SYNTAX_LIST_VALUE_SECURITY_DESCRIPTOR (0x00010009)
#define CLUSPROP_SYNTAX_LIST_VALUE_LARGE_INTEGER (0x0001000a)
#define CLUSPROP_SYNTAX_LIST_VALUE_ULARGE_INTEGER (0x00010006)
#define CLUSPROP_SYNTAX_LIST_VALUE_WORD (0x0001000b)
#define CLUSPROP_SYNTAX_LIST_VALUE_FILETIME (0x0001000c)
#define CLUSPROP_SYNTAX_DISK_SIGNATURE (0x00050002)
#define CLUSPROP_SYNTAX_SCSI_ADDRESS (0x00060002)
#define CLUSPROP_SYNTAX_DISK_NUMBER (0x00070002)
#define CLUSPROP_SYNTAX_PARTITION_INFO (0x00080001)
#define CLUSPROP_SYNTAX_DISK_SERIALNUMBER (0x000a0003)
#define CLUSPROP_SYNTAX_DISK_GUID (0x000b0003)
#define CLUSPROP_SYNTAX_DISK_SIZE (0x000c0006)
#define CLUSPROP_SYNTAX_PARTITION_INFO_EX (0x000d0001)
extern const value_string clusapi_CLUSTER_PROPERTY_SYNTAX_vals[];
int clusapi_dissect_enum_CLUSTER_PROPERTY_SYNTAX(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 *param _U_);
int clusapi_dissect_bitmap_DesiredAccessMask(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_NOTIFY_FILTER_AND_TYPE_RPC(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_NOTIFICATION_DATA_RPC(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_NOTIFICATION_RPC(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_CLUSTER_DISKID(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_CLUSTER_MRR_NODE_RESPONSE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_CLUSTER_MRR_RESPONSE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
int clusapi_dissect_struct_NOTIFICATION_DATA_ASYNC_RPC(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *parent_tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint32 param _U_);
#define DiskIdSignature (0x00000001)
#define DiskIdGuid (0x00000002)
#define DiskIdUnKnown (0x00001388)
extern const value_string clusapi_CLUSDSK_DISKID_ENUM_vals[];
int clusapi_dissect_enum_CLUSDSK_DISKID_ENUM(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSPROP_TYPE_ENDMARK (0x0000)
#define CLUSPROP_TYPE_LIST_VALUE (0x0001)
#define CLUSPROP_TYPE_RESCLASS (0x0002)
#define CLUSPROP_TYPE_NAME (0x0004)
#define CLUSPROP_TYPE_SIGNATURE (0x0005)
#define CLUSPROP_TYPE_SCSIADDRESS (0x0006)
#define CLUSPROP_TYPE_DISK_NUMBER (0x0007)
#define CLUSPROP_TYPE_PARTITION_INFO (0x0008)
#define CLUSPROP_TYPE_DISK_SERIALNUMBER (0x000a)
#define CLUSPROP_TYPE_DISK_GUID (0x000b)
#define CLUSPROP_TYPE_DISK_SIZE (0x000c)
#define CLUSPROP_TYPE_PARTITION_INFO_EX (0x000d)
extern const value_string clusapi_CLUSTER_PROPERTY_TYPE_vals[];
int clusapi_dissect_enum_CLUSTER_PROPERTY_TYPE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSPROP_FORMAT_UNKNOWN (0x0000)
#define CLUSPROP_FORMAT_BINARY (0x0001)
#define CLUSPROP_FORMAT_DWORD (0x0002)
#define CLUSPROP_FORMAT_SZ (0x0003)
#define CLUSPROP_FORMAT_EXPAND_SZ (0x0004)
#define CLUSPROP_FORMAT_MULTI_SZ (0x0005)
#define CLUSPROP_FORMAT_ULARGE_INTEGER (0x0006)
#define CLUSPROP_FORMAT_LONG (0x0007)
#define CLUSPROP_FORMAT_EXPANDED_SZ (0x0008)
#define CLUSPROP_FORMAT_SECURITY_DESCRIPTOR (0x0009)
#define CLUSPROP_FORMAT_LARGE_INTEGER (0x000a)
#define CLUSPROP_FORMAT_WORD (0x000b)
#define CLUSPROP_FORMAT_FILETIME (0x000c)
extern const value_string clusapi_CLUSTER_PROPERTY_FORMAT_vals[];
int clusapi_dissect_enum_CLUSTER_PROPERTY_FORMAT(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUS_CHAR_UNKNOWN (0x00000000)
#define CLUS_CHAR_QUORUM (0x00000001)
#define CLUS_CHAR_DELETE_REQUIRES_ALL_NODES (0x00000002)
#define CLUS_CHAR_LOCAL_QUORUM (0x00000004)
#define CLUS_CHAR_BROADCAST_DELETE (0x00000020)
#define CLUS_CHAR_SINGLE_CLUSTER_INSTANCE (0x00000040)
#define CLUS_CHAR_SINGLE_GROUP_INSTANCE (0x00000080)
#define CLUS_CHAR_COEXIST_IN_SHARED_VOLUME_GROUP (0x00000100)
#define CLUS_CHAR_RESERVED1 (0x00000200)
#define CLUS_CHAR_MONITOR_DETACH (0x00000400)
#define CLUS_CHAR_RESERVED2 (0x00000800)
#define CLUS_CHAR_RESERVED3 (0x00001000)
#define CLUS_CHAR_RESERVED4 (0x00002000)
extern const value_string clusapi_CLUS_CHARACTERISTICS_vals[];
int clusapi_dissect_enum_CLUS_CHARACTERISTICS(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUS_FLAG_CORE (0x00000001)
extern const value_string clusapi_CLUS_FLAGS_vals[];
int clusapi_dissect_enum_CLUS_FLAGS(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define MaintenanceModeTypeDisableIsAliveCheck (1)
#define MaintenanceModeTypeOfflineResource (2)
#define MaintenanceModeTypeUnclusterResource (3)
extern const value_string clusapi_MAINTENANCE_MODE_TYPE_vals[];
int clusapi_dissect_enum_MAINTENANCE_MODE_TYPE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_NODE_STATE (0x00000001)
#define CLUSTER_CHANGE_NODE_DELETED (0x00000002)
#define CLUSTER_CHANGE_NODE_ADDED (0x00000004)
#define CLUSTER_CHANGE_NODE_PROPERTY (0x00000008)
#define CLUSTER_CHANGE_REGISTRY_NAME (0x00000010)
#define CLUSTER_CHANGE_REGISTRY_ATTRIBUTES (0x00000020)
#define CLUSTER_CHANGE_REGISTRY_VALUE (0x00000040)
#define CLUSTER_CHANGE_REGISTRY_SUBTREE (0x00000080)
#define CLUSTER_CHANGE_RESOURCE_STATE (0x00000100)
#define CLUSTER_CHANGE_RESOURCE_DELETED (0x00000200)
#define CLUSTER_CHANGE_RESOURCE_ADDED (0x00000400)
#define CLUSTER_CHANGE_RESOURCE_PROPERTY (0x00000800)
#define CLUSTER_CHANGE_GROUP_STATE (0x00001000)
#define CLUSTER_CHANGE_GROUP_DELETED (0x00002000)
#define CLUSTER_CHANGE_GROUP_ADDED (0x00004000)
#define CLUSTER_CHANGE_GROUP_PROPERTY (0x00008000)
#define CLUSTER_CHANGE_RESOURCE_TYPE_DELETED (0x00010000)
#define CLUSTER_CHANGE_RESOURCE_TYPE_ADDED (0x00020000)
#define CLUSTER_CHANGE_RESOURCE_TYPE_PROPERTY (0x00040000)
#define CLUSTER_CHANGE_CLUSTER_RECONNECT (0x00080000)
#define CLUSTER_CHANGE_NETWORK_STATE (0x00100000)
#define CLUSTER_CHANGE_NETWORK_DELETED (0x00200000)
#define CLUSTER_CHANGE_NETWORK_ADDED (0x00400000)
#define CLUSTER_CHANGE_NETWORK_PROPERTY (0x00800000)
#define CLUSTER_CHANGE_NETINTERFACE_STATE (0x01000000)
#define CLUSTER_CHANGE_NETINTERFACE_DELETED (0x02000000)
#define CLUSTER_CHANGE_NETINTERFACE_ADDED (0x04000000)
#define CLUSTER_CHANGE_NETINTERFACE_PROPERTY (0x08000000)
#define CLUSTER_CHANGE_QUORUM_STATE (0x10000000)
#define CLUSTER_CHANGE_CLUSTER_STATE (0x20000000)
#define CLUSTER_CHANGE_CLUSTER_PROPERTY (0x40000000)
#define CLUSTER_CHANGE_HANDLE_CLOSE (0x80000000)
extern const value_string clusapi_CLUSTER_CHANGE_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSREG_SET_VALUE (1)
#define CLUSREG_CREATE_KEY (2)
#define CLUSREG_DELETE_KEY (3)
#define CLUSREG_DELETE_VALUE (4)
#define CLUSREG_VALUE_DELETED (6)
#define CLUSREG_READ_KEY (7)
#define CLUSREG_READ_VALUE (8)
#define CLUSREG_READ_ERROR (9)
extern const value_string clusapi_CLUSTER_REG_BATCH_COMMAND_vals[];
int clusapi_dissect_enum_CLUSTER_REG_BATCH_COMMAND(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_QUORUM_MAINTAINED (0)
#define CLUSTER_QUORUM_LOST (1)
extern const value_string clusapi_CLUSTER_QUORUM_VALUE_vals[];
int clusapi_dissect_enum_CLUSTER_QUORUM_VALUE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_OBJECT_TYPE_CLUSTER (0x00000001)
#define CLUSTER_OBJECT_TYPE_GROUP (0x00000002)
#define CLUSTER_OBJECT_TYPE_RESOURCE (0x00000003)
#define CLUSTER_OBJECT_TYPE_RESOURCE_TYPE (0x00000004)
#define CLUSTER_OBJECT_TYPE_NETWORK_INTERFACE (0x00000005)
#define CLUSTER_OBJECT_TYPE_NETWORK (0x00000006)
#define CLUSTER_OBJECT_TYPE_NODE (0x00000007)
#define CLUSTER_OBJECT_TYPE_REGISTRY (0x00000008)
#define CLUSTER_OBJECT_TYPE_QUORUM (0x00000009)
#define CLUSTER_OBJECT_TYPE_SHARED_VOLUME (0x0000000a)
extern const value_string clusapi_CLUSTER_OBJECT_TYPE_vals[];
int clusapi_dissect_enum_CLUSTER_OBJECT_TYPE(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_CLUSTER_RECONNECT_V2 (0x00000001)
#define CLUSTER_CHANGE_CLUSTER_STATE_V2 (0x00000002)
#define CLUSTER_CHANGE_CLUSTER_GROUP_ADDED_V2 (0x00000004)
#define CLUSTER_CHANGE_CLUSTER_HANDLE_CLOSE_V2 (0x00000008)
#define CLUSTER_CHANGE_CLUSTER_NETWORK_ADDED_V2 (0x00000010)
#define CLUSTER_CHANGE_CLUSTER_NODE_ADDED_V2 (0x00000020)
#define CLUSTER_CHANGE_CLUSTER_RESOURCE_TYPE_ADDED_V2 (0x00000040)
#define CLUSTER_CHANGE_CLUSTER_COMMON_PROPERTY_V2 (0x00000080)
#define CLUSTER_CHANGE_CLUSTER_PRIVATE_PROPERTY_V2 (0x00000100)
#define CLUSTER_CHANGE_CLUSTER_LOST_NOTIFICATIONS_V2 (0x00000200)
#define CLUSTER_CHANGE_CLUSTER_RENAME_V2 (0x00000400)
extern const value_string clusapi_CLUSTER_CHANGE_CLUSTER_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_CLUSTER_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_GROUP_DELETED_V2 (0x00000001)
#define CLUSTER_CHANGE_GROUP_COMMON_PROPERTY_V2 (0x00000002)
#define CLUSTER_CHANGE_GROUP_PRIVATE_PROPERTY_V2 (0x00000004)
#define CLUSTER_CHANGE_GROUP_STATE_V2 (0x00000008)
#define CLUSTER_CHANGE_GROUP_OWNER_NODE_V2 (0x00000010)
#define CLUSTER_CHANGE_GROUP_PREFERRED_OWNERS_V2 (0x00000020)
#define CLUSTER_CHANGE_GROUP_RESOURCE_ADDED_V2 (0x00000040)
#define CLUSTER_CHANGE_GROUP_RESOURCE_GAINED_V2 (0x00000080)
#define CLUSTER_CHANGE_GROUP_RESOURCE_LOST_V2 (0x00000100)
#define CLUSTER_CHANGE_GROUP_HANDLE_CLOSE_V2 (0x00000200)
extern const value_string clusapi_CLUSTER_CHANGE_GROUP_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_GROUP_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_RESOURCE_COMMON_PROPERTY_V2 (0x00000001)
#define CLUSTER_CHANGE_RESOURCE_PRIVATE_PROPERTY_V2 (0x00000002)
#define CLUSTER_CHANGE_RESOURCE_STATE_V2 (0x00000004)
#define CLUSTER_CHANGE_RESOURCE_OWNER_GROUP_V2 (0x00000008)
#define CLUSTER_CHANGE_RESOURCE_DEPENDENCIES_V2 (0x00000010)
#define CLUSTER_CHANGE_RESOURCE_DEPENDENTS_V2 (0x00000020)
#define CLUSTER_CHANGE_RESOURCE_POSSIBLE_OWNERS_V2 (0x00000040)
#define CLUSTER_CHANGE_RESOURCE_DELETED_V2 (0x00000080)
#define CLUSTER_CHANGE_RESOURCE_DLL_UPGRADED_V2 (0x00000100)
#define CLUSTER_CHANGE_RESOURCE_HANDLE_CLOSE_V2 (0x00000200)
extern const value_string clusapi_CLUSTER_CHANGE_RESOURCE_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_RESOURCE_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_RESOURCE_TYPE_DELETED_V2 (0x00000001)
#define CLUSTER_CHANGE_RESOURCE_TYPE_COMMON_PROPERTY_V2 (0x00000002)
#define CLUSTER_CHANGE_RESOURCE_TYPE_PRIVATE_PROPERTY_V2 (0x00000004)
#define CLUSTER_CHANGE_RESOURCE_TYPE_POSSIBLE_OWNERS_V2 (0x00000008)
#define CLUSTER_CHANGE_RESOURCE_TYPE_DLL_UPGRADED_V2 (0x00000010)
extern const value_string clusapi_CHANGE_RESOURCE_TYPE_V2_vals[];
int clusapi_dissect_enum_CHANGE_RESOURCE_TYPE_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_NETINTERFACE_DELETED_V2 (0x00000001)
#define CLUSTER_CHANGE_NETINTERFACE_COMMON_PROPERTY_V2 (0x00000002)
#define CLUSTER_CHANGE_NETINTERFACE_PRIVATE_PROPERTY_V2 (0x00000004)
#define CLUSTER_CHANGE_NETINTERFACE_STATE_V2 (0x00000008)
#define CLUSTER_CHANGE_NETINTERFACE_HANDLE_CLOSE_V2 (0x00000010)
extern const value_string clusapi_CLUSTER_CHANGE_NETINTERFACE_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_NETINTERFACE_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_NETWORK_DELETED_V2 (0x00000001)
#define CLUSTER_CHANGE_NETWORK_COMMON_PROPERTY_V2 (0x00000002)
#define CLUSTER_CHANGE_NETWORK_PRIVATE_PROPERTY_V2 (0x00000004)
#define CLUSTER_CHANGE_NETWORK_STATE_V2 (0x00000008)
#define CLUSTER_CHANGE_NETWORK_HANDLE_CLOSE_V2 (0x00000010)
extern const value_string clusapi_CLUSTER_CHANGE_NETWORK_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_NETWORK_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_NODE_NETINTERFACE_ADDED_V2 (0x00000001)
#define CLUSTER_CHANGE_NODE_DELETED_V2 (0x00000002)
#define CLUSTER_CHANGE_NODE_COMMON_PROPERTY_V2 (0x00000004)
#define CLUSTER_CHANGE_NODE_PRIVATE_PROPERTY_V2 (0x00000008)
#define CLUSTER_CHANGE_NODE_STATE_V2 (0x00000010)
#define CLUSTER_CHANGE_NODE_GROUP_GAINED_V2 (0x00000020)
#define CLUSTER_CHANGE_NODE_GROUP_LOST_V2 (0x00000040)
#define CLUSTER_CHANGE_NODE_HANDLE_CLOSE_V2 (0x00000080)
extern const value_string clusapi_CLUSTER_CHANGE_NODE_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_NODE_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_REGISTRY_ATTRIBUTES_V2 (0x00000001)
#define CLUSTER_CHANGE_REGISTRY_NAME_V2 (0x00000002)
#define CLUSTER_CHANGE_REGISTRY_SUBTREE_V2 (0x00000004)
#define CLUSTER_CHANGE_REGISTRY_VALUE_V2 (0x00000008)
#define CLUSTER_CHANGE_REGISTRY_HANDLE_CLOSE_V2 (0x00000010)
extern const value_string clusapi_CLUSTER_CHANGE_REGISTRY_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_REGISTRY_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_QUORUM_STATE_V2 (0x00000001)
extern const value_string clusapi_CLUSTER_CHANGE_QUORUM_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_QUORUM_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#define CLUSTER_CHANGE_SHARED_VOLUME_STATE_V2 (0x00000001)
extern const value_string clusapi_CLUSTER_CHANGE_SHARED_VOLUME_V2_vals[];
int clusapi_dissect_enum_CLUSTER_CHANGE_SHARED_VOLUME_V2(tvbuff_t *tvb _U_, int offset _U_, packet_info *pinfo _U_, proto_tree *tree _U_, dcerpc_info* di _U_, guint8 *drep _U_, int hf_index _U_, guint1632 *param _U_);
#endif /* __PACKET_DCERPC_CLUSAPI_H */
