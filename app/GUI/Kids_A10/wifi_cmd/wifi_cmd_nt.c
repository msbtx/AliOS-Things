#include <stdio.h>
#include "stm32l4xx_hal.h"
#include "wifi_cmd_nt.h"
#include <k_api.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define wifi_uart brd_uart1_dev
#define os_uart uart_0
#define UART1_PORT 0
#define UART2_PORT 1
#if 0
static void notion_get_version(char *cmd)
{
	char buff_rev[100] = {0};
	char ch;
	int rec_cnt = 0;
	int exp_cnt = 0;
	int ap_cnt = 0, cnt = 0;
	int ret;

	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);
		
	cnt = 0;
	memset(buff_rev, 0, 100);
	while(1){
		ret = hal_uart_recv(&wifi_uart, (void *)&ch, 1, &exp_cnt, 10000);
			if(ret == 0){
				buff_rev[cnt++] = ch;
				if(cnt > 8){
					if((buff_rev[cnt - 1] == '\n') && (buff_rev[cnt - 2] == '\r')){
						break;
					}
				}
			}
			else {
				printf("ret = %d\n", ret);
				break;
			}
			
	}
		
	if(ret == 0)
		printf("%s\n", buff_rev);
	else
		printf("get version error\n");
}

static void notion_wifiscan_Command(char *cmd)
{
	char buff_rev[33][50] = {0};
	char ch;
	int rec_cnt = 0;
	int exp_cnt = 0;
	int ap_cnt = 0, cnt = 0;
	int ret;

	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);
		
  	while(1){
			ret = hal_uart_recv(&wifi_uart, (void *)&ch, 1, &exp_cnt, 10000);
			if(ret == 0){
				buff_rev[0][rec_cnt++] = ch;
				if(rec_cnt > 6){
					if((buff_rev[0][rec_cnt - 1] == '\n') && (buff_rev[0][rec_cnt - 2] == '\r')){
						rec_cnt = 0;
						sscanf((buff_rev[0] + 2), "Got %d AP", &ap_cnt);
						rec_cnt = 0;
						break;
					}
				}
			}
			else {
				printf("ret = %d\n", ret);
				break;
			}
	}

	cnt = 0;
	memset(buff_rev[cnt + 1], 0, 50);
	while(cnt < ap_cnt ){
		ret = hal_uart_recv(&wifi_uart, (void *)&ch, 1, &exp_cnt, 10000);
			if(ret == 0){
				buff_rev[cnt + 1][rec_cnt++] = ch;
				if(rec_cnt > 3){
					if((buff_rev[cnt + 1][rec_cnt - 1] == '\n') && (buff_rev[cnt + 1][rec_cnt - 2] == '\r')){
						rec_cnt = 0;
						cnt++;
						if(cnt < ap_cnt)
							memset(buff_rev[cnt + 1], 0, 50);
					}
				}
			}
			else {
				printf("ret = %d\n", ret);
				break;
			}
			
	}
		
	cnt = 0;
	printf("Got %d AP:\r\n", ap_cnt);
	while(cnt < ap_cnt ){
		printf("ssid%d : %s\r\n", cnt+1, buff_rev[cnt + 1]);
		cnt++;
	}
}

static void notion_sta_Command(char *cmd)
{
	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);		
}

static void notion_wifistate_Command(char *cmd)
{
	char buff_rev[100] = {0};
	char ch;
	int rec_cnt = 0;
	int exp_cnt = 0;
	int ap_cnt = 0, cnt = 0;
	int ret;

	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);
		
	cnt = 0;
	memset(buff_rev, 0, 100);
	while(1){
		ret = hal_uart_recv(&wifi_uart, (void *)&ch, 1, &exp_cnt, 10000);
			if(ret == 0){
				buff_rev[cnt++] = ch;
				if(cnt > 45){
					if((buff_rev[cnt - 1] == '\n') && (buff_rev[cnt - 2] == '\r')){
						break;
					}
				}
			}
			else {
				printf("ret = %d\n", ret);
				break;
			}
			
	}
		
	if(ret == 0)
		printf("%s\n", buff_rev);
	else
		printf("get wifi state error\n");
}

static const struct nt_cli_command built_ins[] =
{
    {"version", NULL, notion_get_version},
   // {"echo", NULL, notion_echo_cmd_handler},
  //  {"exit", "CLI exit", notion_cli_exit_handler},

    /// WIFI
    {"scan", "scan ap", notion_wifiscan_Command},
   // {"advscan", "scan ap", notion_wifiadvscan_Command},
   // {"softap", "softap ssid key", notion_softap_Command},
   // {"stopintf", "stopintf intfacename", notion_stop_wlan_intface_Command},    
    {"sta", "sta ap_ssid key", notion_sta_Command},
   // {"adv", "adv", notion_sta_adv_Command},
    //{"mtr", "mtr channel", notion_mtr_Command},
    //{"addif", "addif param", notion_add_virtual_intface},
    //{"delif", "delif role", notion_del_virtual_intface},
    //{"showif", "show", notion_show_virtual_intface},   
    {"wifistate", "Show wifi state", notion_wifistate_Command},
#if 0
    // network
    {"ifconfig", "Show IP address", notion_ifconfig_Command},
    {"ping", "ping <ip>", notion_ping_Command},
    {"dns", "show/clean/<domain>", notion_dns_Command},
    {"sockshow", "Show all sockets", notion_socket_show_Command},
    // os
    {"tasklist", "list all thread name status", notion_task_Command},

    // others
    {"memshow", "print memory information", notion_memory_show_Command},
    {"memdump", "<addr> <length>", notion_memory_dump_Command},
    {"os_memset", "<addr> <value 1> [<value 2> ... <value n>]", notion_memory_set_Command},
    {"memp", "print memp list", memp_dump_Command},

    {"reboot", "reboot system", notion_reboot},

    {"time",     "system time",                 notion_uptime_Command},
//    {"ota",      "system ota",                  ota_Command},
    {"flash",    "Flash memory map",            notion_partShow_Command},
#endif
    {NULL, NULL, NULL},
};

static int look_up_cmd(char *cmd)
{
	int index = 0, cmd_index = -1;
	//struct nt_cli_command *command = NULL;

	while(built_ins[index].name){
		if(strcmp(built_ins[index].name, cmd) == 0){
			cmd_index = index;
			break;
		}
		else
			index++;
	}
	return cmd_index;
}

static void pre_hand_cmd(char *buff_cmd, char *cmd)
{
	char *p = buff_cmd;
	while(*p == ' ')
		p++;
	while((*p) && (*p != ' ')){
		*cmd++ = *p++;
	}
	*cmd = '\0';
}

void wifi_cmd_task(void *arg)
{
	//struct nt_cli_command *command = NULL;
	int cmd_index = -1, ret, rev_cnt;
	char buff_cmd[100] = {0};
	char cmd[20] = {0};
	char icnt;
	char gch;
	
	printf("wifi_cmd_task\n");
	while(1){	
		cmd_index = -1;
		icnt = 0;
		memset(buff_cmd, 0, sizeof(100));
		while(1){
				ret = hal_uart_recv(&os_uart, (void *)&gch, 1, &rev_cnt, 10000);
				if(ret == 0){
					if(gch == '\r'){
						buff_cmd[icnt] = '\0';
						break;
					}
					else {
						buff_cmd[icnt++] = gch;
						if(icnt >= 100)
							break;
					}
				}
				else {
					break;
				}
		}
		if(ret != 0)
			continue;
		pre_hand_cmd(buff_cmd, cmd);
		printf("cmd = %s\n", cmd);
		cmd_index = look_up_cmd(cmd);
		printf("buff_cmd = %s\n", buff_cmd);
		printf("cmd_index = %d\n", cmd_index);
		
		if(cmd_index >= 0){
			built_ins[cmd_index].function(buff_cmd);
		}
		//krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND);
	}
}

#else
static void notion_wifistate_Command(char *cmd)
{
	char buff_rev[100] = {0};
	char ch;
	int rec_cnt = 0;
	int exp_cnt = 0;
	int ap_cnt = 0, cnt = 0;
	int ret;
	int time = 0;
	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);
		
	cnt = 0;
	memset(buff_rev, 0, 100);
	while(1){
		exp_cnt = uart_get_fifo_data_size(UART1_PORT); 
		if(exp_cnt){
			time = 0;
			ret = uart_get_fifo_data(UART1_PORT, (void *)&ch, 1);
			if(ret == 1){
				buff_rev[cnt++] = ch;
				if(cnt > 45){
					if((buff_rev[cnt - 1] == '\n') && (buff_rev[cnt - 2] == '\r')){
						break;
					}
				}
			}
		}	
		else {
			krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND / 3);
			time++;
			if(time > 9){
				printf("time out\r\n");
			}
		}
	}
		
	printf("%s\n", buff_rev);
}

static void notion_sta_Command(char *cmd)
{
	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);		
}

static void notion_wifiscan_Command(char *cmd)
{
	char buff_rev[33][50] = {0};
	char ch;
	int rec_cnt = 0;
	int exp_cnt = 0;
	int ap_cnt = 0, cnt = 0;
	int ret;
	int time = 0; 

	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);
	rec_cnt = 0;
  	while(1){
			exp_cnt = uart_get_fifo_data_size(UART1_PORT);
			if(exp_cnt){
				time = 0;
				ret = uart_get_fifo_data(UART1_PORT, (void *)&ch, 1);
				if(ret == 1){
					buff_rev[0][rec_cnt++] = ch;
					if(rec_cnt > 6){
						if((buff_rev[0][rec_cnt - 1] == '\n') && (buff_rev[0][rec_cnt - 2] == '\r')){
							rec_cnt = 0;
							sscanf((buff_rev[0] + 2), "Got %d AP", &ap_cnt);
							rec_cnt = 0;
							break;
						}
					}
				}
			}
			else {
				krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND / 3);
				time++;
				if(time > 15){
					printf("time out\r\n");
				}
			}
	}

	cnt = 0;
	memset(buff_rev[cnt + 1], 0, 50);
	while(cnt < ap_cnt ){
		exp_cnt = uart_get_fifo_data_size(UART1_PORT);
		if(exp_cnt){
			time = 0;
			ret = uart_get_fifo_data(UART1_PORT, (void *)&ch, 1);
			if(ret == 1){
				buff_rev[cnt + 1][rec_cnt++] = ch;
				if(rec_cnt > 3){
					if((buff_rev[cnt + 1][rec_cnt - 1] == '\n') && (buff_rev[cnt + 1][rec_cnt - 2] == '\r')){
						rec_cnt = 0;
						cnt++;
						if(cnt < ap_cnt)
							memset(buff_rev[cnt + 1], 0, 50);
					}
				}
			}
		}
		else {
			krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND / 3);
			time++;
			if(time > 9){
				printf("time out\r\n");
			}
		}
	}
		
	cnt = 0;
	printf("Got %d AP:\r\n", ap_cnt);
	while(cnt < ap_cnt ){
		printf("ssid%02d : %s", cnt+1, buff_rev[cnt + 1]);
		cnt++;
	}
}

static void notion_get_version(char *cmd)
{
	char buff_rev[100] = {0};
	char ch;
	//int rec_cnt = 0;
	int exp_cnt = 0;
	int ap_cnt = 0, cnt = 0;
	int ret;
	int time = 0;

	hal_uart_send(&wifi_uart, (void *)cmd, strlen(cmd), 30000);
	hal_uart_send(&wifi_uart, (void *)"\r", 1, 30000);
	hal_uart_send(&wifi_uart, (void *)"\n", 1, 30000);
		
	cnt = 0;
	memset(buff_rev, 0, 100);
	while(1){
		exp_cnt = uart_get_fifo_data_size(UART1_PORT);
		if(exp_cnt > 0){
			//ret = hal_uart_recv(&wifi_uart, (void *)&ch, 1, &exp_cnt, 10000);
			ret = uart_get_fifo_data(UART1_PORT, &ch, 1);
			if(ret == 1){
				buff_rev[cnt++] = ch;
				if(cnt > 8){
					if((buff_rev[cnt - 1] == '\n') && (buff_rev[cnt - 2] == '\r')){
						break;
					}
				}
			}
			else {
				printf("uart_get_fifo_data error\r\n");
				break;
			}
		}
		else {
			krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND / 3);
			time++;
			if(time > 9){
				printf("time out\r\n");
			}
		}
	}
	printf("%s\n", buff_rev);
}

static const struct nt_cli_command built_ins[] =
{
    {"version", NULL, notion_get_version},
    /// WIFI
    {"scan", "scan ap", notion_wifiscan_Command},
   // {"advscan", "scan ap", notion_wifiadvscan_Command},
   // {"softap", "softap ssid key", notion_softap_Command},
   // {"stopintf", "stopintf intfacename", notion_stop_wlan_intface_Command},    
    {"sta", "sta ap_ssid key", notion_sta_Command},
  
    {"wifistate", "Show wifi state", notion_wifistate_Command},
    {NULL, NULL, NULL},
};

static int look_up_cmd(char *cmd)
{
	int index = 0, cmd_index = -1;
	//struct nt_cli_command *command = NULL;

	while(built_ins[index].name){
		if(strcmp(built_ins[index].name, cmd) == 0){
			cmd_index = index;
			break;
		}
		else
			index++;
	}
	return cmd_index;
}

static void pre_hand_cmd(char *buff_cmd, char *cmd)
{
	char *p = buff_cmd;
	while(*p == ' ')
		p++;
	while((*p) && (*p != ' ')){
		*cmd++ = *p++;
	}
	*cmd = '\0';
}

void wifi_cmd_task(void *arg)
{
	//struct nt_cli_command *command = NULL;
	int cmd_index = -1, ret, rev_cnt;
	char buff_cmd[100] = {0};
	char cmd[20] = {0};
	char icnt;
	char gch;
	
	printf("wifi_cmd_task\n");
	uart_init_isr_and_buff(&wifi_uart, UART1_PORT);
	uart_init_isr_and_buff(&os_uart, UART2_PORT);
	while(1){	
		cmd_index = -1;
		icnt = 0;
		memset(buff_cmd, 0, sizeof(100));
		while(1){
			rev_cnt = uart_get_fifo_data_size(UART2_PORT);
			if(rev_cnt > 0){
				ret = uart_get_fifo_data(UART2_PORT, &gch, 1);
				if(ret == 1){
					if(gch == '\r'){
						buff_cmd[icnt] = '\0';
						break;
					}
					else {
						buff_cmd[icnt++] = gch;
						if(icnt >= 100)
							break;
					}
				}
			}
		}
		//if(ret != 1)
		//	continue;
		pre_hand_cmd(buff_cmd, cmd);
		printf("cmd = %s\n", cmd);
		cmd_index = look_up_cmd(cmd);
		printf("buff_cmd = %s\n", buff_cmd);
		printf("cmd_index = %d\n", cmd_index);
		
		if(cmd_index >= 0){
			built_ins[cmd_index].function(buff_cmd);
		}
		//krhino_task_sleep(RHINO_CONFIG_TICKS_PER_SECOND);
	}
}
#endif
