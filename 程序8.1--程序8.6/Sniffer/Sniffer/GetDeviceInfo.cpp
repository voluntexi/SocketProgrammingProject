//GetDeviceInfo.cpp��ȡ�豸�б�
#include "pcap.h"
int main()
{
	pcap_if_t *alldevs;
	pcap_if_t *d;
	int i=0;
	char errbuf[PCAP_ERRBUF_SIZE];
	/* ��ȡ���ػ����豸�б� */
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL /* ����Ҫ��֤*/, &alldevs, errbuf) == -1)
	{
		fprintf(stderr,"pcap_findalldevs_ex�����豸�б����: %s\n", errbuf);
		exit(1);
	}
	/* ��ӡ�б� */
	for(d= alldevs; d != NULL; d= d->next)
	{
		printf("%d. %s", ++i, d->name);
		if (d->description)
		printf(" (%s)\n", d->description);
		else
		printf(" (��������Ϣ)\n");
	}
	if (i == 0)
	{
		printf("\nû���ҵ��豸�б�! ȷ��WinPcap�Ѿ���ȷ��װ...\n");
		return 0;
	}
	/* ������Ҫ�豸�б��ˣ��ͷ��� */
	pcap_freealldevs(alldevs);
	return 0;
}