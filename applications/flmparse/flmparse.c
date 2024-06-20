/*
 * flmparse.c
 *
 *  Created on: 2021年4月10日
 *      Author: hello
 */

//来源：https://gitee.com/jhembedded/flmparse   @MIT


#include <rtthread.h>
#include <dfs_posix.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include "elf.h"
#include "FlashOS.h"

#define LOG_TAG     "flmparse"     // 该模块对应的标签。不定义时，默认：NO_TAG
#define LOG_LVL     LOG_LVL_DBG   // 该模块对应的日志输出级别。不定义时，默认：调试级别
#include <ulog.h>                 // 必须在 LOG_TAG 与 LOG_LVL 下面

static int ReadDataFromFile(char* FName, uint32_t offset, void* buf, uint32_t size);
static int FLM_Prase(char* FName, void* pBuffer, uint32_t* Size, uint32_t* Init, uint32_t* UnInit, uint32_t* EraseChip, uint32_t* EraseSector, uint32_t* ProgramPage);

static uint32_t RAM[2560] = {0};
uint32_t static Addr[5] = {0x000003C9,0x00000405,0x00000081,0x00000089,0x000003D9};
//uint32_t static Addr[5] = {0};

FlashDevice_T target_device;
	
int parse_flm_file(int argc, char* argv[])
{
    int i = 0;
    uint32_t Size = 0;

    if(argc != 2)
    {
        rt_kprintf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
        rt_kprintf("Usage:\n");
        rt_kprintf("        parse_flm_file [filename]\n");
        rt_kprintf("\n\n");
        goto __exit;
    }

    /* 这8个数是中断halt程序，让函数执行完后返回到这里来执行从而让CPU自动halt住 */
    RAM[0] = 0xE00ABE00;
    RAM[1] = 0x062D780D;
    RAM[2] = 0x24084068;
    RAM[3] = 0xD3000040;
    RAM[4] = 0x1E644058;
    RAM[5] = 0x1C49D1FA;
    RAM[6] = 0x2A001E52;
    RAM[7] = 0x4770D1F2;

    if(FLM_Prase(argv[1], &RAM[8], &Size, &Addr[0],&Addr[1],&Addr[2],&Addr[3],&Addr[4]) < 0)
    {
        rt_kprintf("错误：解析FLM格式文件失败，请检查FLM文件是否存在或格式正确性！\r\n");
        goto __exit;
    }

    rt_kprintf("\r\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\r\n");

    Size += 32;

    rt_kprintf("\r\nstatic const uint32_t flash_code[] = \n{");
    for(i = 0; i < (Size >> 2); i++)
    {
        if(i % 8 == 0)
        {
            rt_kprintf( "\n    ");
        }
        rt_kprintf("0X%08X,", RAM[i]);
    }
    rt_kprintf( "\n};\n");

    rt_kprintf( "\r\nconst program_target_t flash_algo =\n{\n");
    rt_kprintf( "    0X20000020 + 0X%08X,  // Init\n",        Addr[0]);
    rt_kprintf( "    0X20000020 + 0X%08X,  // UnInit\n",      Addr[1]);
    rt_kprintf( "    0X20000020 + 0X%08X,  // EraseChip\n",   Addr[2]);
    rt_kprintf( "    0X20000020 + 0X%08X,  // EraseSector\n", Addr[3]);
    rt_kprintf( "    0X20000020 + 0X%08X,  // ProgramPage\n", Addr[4]);
    rt_kprintf( "\n");
    rt_kprintf( "    // BKPT : start of blob + 1\n");
    rt_kprintf( "    // RSB  : address to access global/static data\n");
    rt_kprintf( "    // RSP  : stack pointer\n");
    rt_kprintf( "    {\n");
    rt_kprintf( "        0X20000001,\n");
    rt_kprintf( "        0X20000C00,\n");
    rt_kprintf( "        0X20001000,\n");
    rt_kprintf( "    },\n");
    rt_kprintf( "\n");
    rt_kprintf( "    0x20000400,                      // mem buffer location\n");
    rt_kprintf( "    0x20000000,                      // location to write prog_blob in target RAM\n");
    rt_kprintf( "    sizeof(flash_code),              // prog_blob size\n");
    rt_kprintf( "    flash_code,                      // address of prog_blob\n");
    rt_kprintf( "    0x00000400,                      // ram_to_flash_bytes_to_be_written\n");
    rt_kprintf( "};\n");
    rt_kprintf( "\n");
    rt_kprintf( "\n");
    rt_kprintf( "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n");

__exit:
    return 0;
}
MSH_CMD_EXPORT(parse_flm_file , parse_flm_file);


//static int ReadDataFromFile(char* FName, uint32_t offset, void* buf, uint32_t size)
//{
//    int ret = 0;
//    int fd = 0;

//    if ((fd = open(FName, O_RDONLY | O_BINARY)) < 0)
//    {
//        ret = -1;
//        goto __exit;
//    }

//    if (lseek(fd, offset, SEEK_SET) < 0)
//    {
//        ret = -2;
//        goto __exit;
//    }

//    if (read(fd, buf, size) != size)
//    {
//        ret = -3;
//        goto __exit;
//    }

//__exit:
//    close(fd);
//    return ret;
//}

static int ReadDataFromFile(char* FName, uint32_t offset, void* buf, uint32_t size)
{
    int ret = 0;
    int fd = 0;
    ssize_t read_bytes;

	LOG_D("wait for read file size is %d",size);
    if ((fd = open(FName, O_RDONLY | O_BINARY)) < 0)
    {
        LOG_E("Error opening file");
        ret = -1;
        goto __exit;
    }

    if (lseek(fd, offset, SEEK_SET) < 0)
    {
        LOG_E("Error seeking in file");
        ret = -2;
        goto __exit;
    }

    read_bytes = read(fd, buf, size);
    if (read_bytes < 0)
    {
        LOG_E("Error reading file");
        ret = -3;
        goto __exit;
    }
    if (read_bytes != size)
    {
        LOG_E("Expected to read %u bytes, but only read %zd bytes.\n", size, read_bytes);
        ret = -3;
        goto __exit;
    }

__exit:
    close(fd);
    return ret;
}

int FLM_Prase(char* FName, void* pBuffer, uint32_t* Size, uint32_t* Init, uint32_t* UnInit, uint32_t* EraseChip, uint32_t* EraseSector, uint32_t* ProgramPage)
{
#define LOAD_FUN_NUM 5

	uint8_t* buffer = rt_malloc(2048);  // 动态分配内存
    if (buffer == NULL)                 // 检查内存分配是否成功
    {
		LOG_E("rt_malloc fail!");
        return -1;  // 内存分配失败
    }
	
    uint32_t i = 0, k = 0;
    int found = 0;
    const Elf32_Phdr* pPhdr = (const Elf32_Phdr *) buffer;
    const Elf32_Shdr* pShdr = (const Elf32_Shdr *) buffer;
    const Elf32_Sym* pSymbol = (const Elf32_Sym *) buffer;
    Elf32_Ehdr ehdr = {0};      // ELF文件信息头
    Elf32_Shdr ShdrSym = {0};   // 符号表头
    Elf32_Shdr ShdrStr = {0};   // 字符串表头
    const char* StrFunNameTable[LOAD_FUN_NUM] = { "Init", "UnInit", "EraseChip", "EraseSector", "ProgramPage"};

    int StrFunIndexTable[LOAD_FUN_NUM] = {-1, -1, -1, -1, -1};

    //
    // 读取ELF文件头信息（ELF Header）
    //
    ReadDataFromFile(FName, 0, &ehdr, sizeof(Elf32_Ehdr));

    // 不是ELF格式文件
    if (rt_strstr((const char *)ehdr.e_ident, "ELF") == NULL)
    {
		rt_free(buffer);  // 释放内存
        return -1;
    }

    //
    // 读取程序头信息（Program Header）
    //
    ReadDataFromFile(FName, ehdr.e_phoff, buffer, sizeof(Elf32_Phdr) * ehdr.e_phnum);
    for (i = 0; i < ehdr.e_phnum; i++)
    {
        if (pPhdr[i].p_type == PT_LOAD && (pPhdr[i].p_flags & (PF_X | PF_W | PF_R)) == (PF_X | PF_W | PF_R))
        {
            if (pPhdr[i].p_filesz > sizeof(RAM))  // RAM代码过大
            {
				rt_free(buffer);  // 释放内存
                return -2;
            }
            if(ReadDataFromFile(FName, pPhdr[i].p_offset, pBuffer, pPhdr[i].p_filesz) < 0)  // 提取需要下载到RAM的程序代码
            {
				rt_free(buffer);  // 释放内存
                return -3;
            }
            LOG_D("the file size=:%d\r\n", pPhdr[i].p_filesz);
            *Size = pPhdr[i].p_filesz;
        }
        else if ((pPhdr[i].p_type == PT_LOAD)&&(i == 1))
        {
            ReadDataFromFile(FName, pPhdr[i].p_offset, &target_device, pPhdr[i].p_filesz);
        }
    }

    //
    // 读取节区头部（Sections Header）
    //
    ReadDataFromFile(FName, ehdr.e_shoff, buffer, sizeof(Elf32_Shdr) * ehdr.e_shnum);

    // 查找符号表头并拷贝出来备用
    for (i = 0; i < ehdr.e_shnum; i++)
    {
        if (pShdr[i].sh_type == SHT_SYMTAB)
        {
            rt_memcpy(&ShdrSym, &pShdr[i], sizeof(Elf32_Shdr));

            // 查找字符串表头并拷贝出来备用
            if (pShdr[ShdrSym.sh_link].sh_type == SHT_STRTAB)
            {
                rt_memcpy(&ShdrStr, &pShdr[ShdrSym.sh_link], sizeof(Elf32_Shdr));
                found = 1;
                break;
            }
        }
    }

    if(!found)
    {
		rt_free(buffer);  // 释放内存
        return -4;
    }

    //
    // 根据字符串表头读取所有字符串表
    //
    ReadDataFromFile(FName, ShdrStr.sh_offset, buffer, ShdrStr.sh_size);

    for (i = 0; i < ShdrStr.sh_size; i++)    
	{
		if (buffer[i] == '\0')    
		{
		buffer[i] = '\n';
		}
	}
    buffer[ShdrStr.sh_size] = 0;
    for (i = 0; i < LOAD_FUN_NUM; i++)
    {
        char* p = NULL;

        if(StrFunNameTable[i] == NULL)
            continue;

        if((p = rt_strstr((const char *) buffer, StrFunNameTable[i])) == NULL)
            continue;

        StrFunIndexTable[i] = (uint32_t) p - (uint32_t) buffer;
		LOG_D("Checking function: %s,StrFunIndexTable :%0X", StrFunNameTable[i],StrFunIndexTable[i]);
    }

	
    //
    // 读取符号表
    //
    ReadDataFromFile(FName, ShdrSym.sh_offset, buffer, ShdrSym.sh_size);
	
    // 遍历查询我们用到的函数符号
    for (i = 0; i < ShdrSym.sh_size / sizeof(Elf32_Sym); i++, pSymbol++)
    {
//		LOG_D("loop i is:%d", i);
        for (k = 0; k < LOAD_FUN_NUM; k++)
        {
//			LOG_D("loop k is:%d", k);
            if (StrFunIndexTable[k] >= 0 && StrFunIndexTable[k] == pSymbol->st_name)  // symbol.st_name的值就是偏移地址
            {
//				LOG_D("pSymbol->st_value is:%x", pSymbol->st_value);
                switch (k)
                {
                case 0:
                    *Init = pSymbol->st_value;
                    break;
                case 1:
                    *UnInit = pSymbol->st_value;
                    break;
                case 2:
                    *EraseChip = pSymbol->st_value;
                    break;
                case 3:
                    *EraseSector = pSymbol->st_value;
                    break;
                case 4:
                    *ProgramPage = pSymbol->st_value;
                    break;
                default:
                    break;
                }
            }
        }
    }

	rt_free(buffer);  // 释放内存
    return 0;
}

uint32_t * get_flm_flash_blob_addr(void)
{
    return &RAM[0];
}
uint32_t get_flm_flash_algo_init_addr(void)
{
    return Addr[0]+0X20000020;
}
uint32_t get_flm_flash_algo_uninit_addr(void)
{
    return Addr[1]+0X20000020;
}
uint32_t get_flm_flash_algo_erase_chip_addr(void)
{
    return Addr[2]+0X20000020;
}
uint32_t get_flm_flash_algo_erase_sector_addr(void)
{
    return Addr[3]+0X20000020;
}
uint32_t get_flm_flash_algo_program_page_addr(void)
{
    return Addr[4]+0X20000020;
}


uint32_t parse_flm_from_file(char* _file_path)
{
    uint32_t Size = 0;

    /* 这8个数是中断halt程序，让函数执行完后返回到这里来执行从而让CPU自动halt住 */
    RAM[0] = 0xE00ABE00;
    RAM[1] = 0x062D780D;
    RAM[2] = 0x24084068;
    RAM[3] = 0xD3000040;
    RAM[4] = 0x1E644058;
    RAM[5] = 0x1C49D1FA;
    RAM[6] = 0x2A001E52;
    RAM[7] = 0x4770D1F2;

    if(FLM_Prase(_file_path, &RAM[8], &Size, &Addr[0],&Addr[1],&Addr[2],&Addr[3],&Addr[4]) < 0)
    {
        LOG_E("Error: Failed to parse FLM format file, please check whether the FLM file exists or the format is correct!\r\n");
        return 0;
    }

    Size += 32;

    return Size;
}


