#ifndef __GEODATA_H__
#define __GEODATA_H__
#include <stdint.h>
/**************************************************************
| geo_head_t |const_index_t[geo_head_t.const_count] | const table |geo_item_t[geo_head_t.geo_item_count] |
sizeof(const table) = geo_head_t.geo_item_offset-geo_head_t.const_table_offset
***************************************************************/

#define GEODATA_MAGIC 0x9E00

typedef struct {
	uint32_t magic;
	uint32_t const_count; //常量数量
	uint32_t const_table_offset;
	uint32_t geo_item_count;
	uint32_t geo_item_offset;
	uint32_t filesize; //geo文件大小。
	char rest[8]; //保留字段。
}geo_head_t;

/**
 * 常量索引
 */
typedef struct {
	int begin;  	//begin 是相对于常量区的偏移。
	int len;		//常量串长度，包括一个\0
}const_index_t;

typedef struct {
	uint32_t ip_begin;
	uint32_t ip_end;
	uint32_t province; 
	uint32_t city;
	uint32_t isp;
}geo_item_t;

typedef struct {
	uint32_t ip_begin;
	uint32_t ip_end;
	const char* province;
	int province_len;
	const char* city;
	int city_len;
	const char* isp;
	int isp_len;
}geo_result_t;

typedef struct {
	char* ptr;
	uint32_t size;
}geo_ctx_t;

#define cvalue(indexs,buf, index) (&buf[indexs[index].begin])
#define clength(indexs, index) (indexs[index].len)
geo_ctx_t* geo_new();
int geo_init(geo_ctx_t* geo_ctx, const char* geodatafile);
void geo_destroy(geo_ctx_t* geo_ctx);
int geo_find2(geo_ctx_t* geo_ctx, uint32_t ip, geo_result_t* result);
int geo_find(geo_ctx_t* geo_ctx, const char* ip, geo_result_t* result);

/// utils 
const char* long2ip(uint32_t ip_long);
uint32_t ip2long(const char *ip,int len);

#endif
