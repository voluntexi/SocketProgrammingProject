//GetDeviceInfo.cpp获取设备列表
#include "pcap.h"
int main()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	/* 获取本地机器设备列表 */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* 不需要认证*/, &alldevs, errbuf) == -1)
	{
		fprintf(stderr,"pcap_findalldevs_ex返回设备列表错误: %s\n", errbuf);
		exit(1);
	}
	/* 打印列表 */
	for(d= alldevs; d != NULL; d= d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
		printf(" (%s)\n", d->description);
		else
		printf(" (无描述信息)\n");
	}
	if (i == 0)
	{
		printf("\n没有找到设备列表! 确认WinPcap已经正确安装...\n");
		return 0;
	}
	/* 不再需要设备列表了，释放它 */
	pcap_freealldevs(alldevs);
	return 0;
}