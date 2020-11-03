#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include <stdlib.h>
#pragma comment(lib,"..\\WS2_32.Lib")   //���� ws2_32.dll
#define maxnum  1000
#define BUF_SIZE 500
#define INFO_SIZE 15

int split_str(char* mySendStr);
char* dataArrOne[INFO_SIZE];
void sortOutPath(char* routerPathStr);
int dataArrTwo[100][100];

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET servSock;
	SOCKADDR_IN sockAddr;
	SOCKADDR clntAddr;
	int nSize, arrSize, allSize, matrixSize,x,y;//matrixSize�����С
	char buffer[BUF_SIZE];

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//�����׽���
	servSock = socket(AF_INET, SOCK_STREAM, 0);
	//���׽���
	
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;  //ʹ��IPv4��ַ
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //�����IP��ַ
	sockAddr.sin_port = htons(1234);  //�˿�
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//�������״̬
	listen(servSock, 20);
	
	nSize = sizeof(SOCKADDR);
    arrSize = 0;
	while (1)
	{
		char* ptr;
		char* ptrData;
		int infoSize;//�������
		int x,y,a,b,index;
		float result;
		int dist[maxnum];//����·��
		int pre[maxnum];     // ��¼��ǰ���ǰһ�����
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);
		//send(clntSock, buffer, strLen, 0);
		char arrData[BUF_SIZE];
		memcpy(&arrData, buffer, BUF_SIZE);
        // �ж����ݷ����Ƿ����,ͳ��Ԫ�ظ���
        if(strcmp("q", arrData) == 0){
            printf("���ݷ������\n");
            // ��Ԫ����������Ϊ0
            allSize = arrSize;

            // ������ά����
            // 1. ���ά�����С
            matrixSize = sqrt(allSize);
            printf("�����С�ǣ�%dx%d\n", matrixSize, matrixSize);

            // 2. ��������
            for(x=0; x<matrixSize; x++){
                for(y=0; y<matrixSize; y++){
                    printf("%d\t", dataArrTwo[x][y]);
                }
                printf("\n");
            }
            arrSize = 0;
        }else{
            // printf("%s\n",arrData);
            infoSize = split_str(arrData);
            // printf("info_size:%d\n", infoSize);
            printf("routerPath:%s\n", dataArrOne[8]);

            // �����ַ���Ϊ��ά��������
            sortOutPath(dataArrOne[8]);
            arrSize++;
        }
        
	}
	//�ر��׽���
	closesocket(servSock);
	//��ֹ DLL ��ʹ��
	WSACleanup();
	return 0;
}

// ����·������
void sortOutPath(char* routerPathStr){
    char* p;
    int x,y, weight;
    p=strtok(routerPathStr,":");
    p = strtok(NULL,":");

    // ȥ��������
    p = strtok(p, "'");
    p = strtok(p, "'");
    
    printf("%s\n",p);
    

    // ȥ��-��
    p = strtok(p, "-");
    // printf("x:%s\t",p);
    // ���ַ���ת������
    x = atoi(p);
    p = strtok(NULL,"-");
    // printf("y:%s\t",p);
    y = atoi(p);
    p = strtok(NULL,"-");
    // printf("weight:%s\n",p);
    weight = atoi(p);
    
    // �����ݴ浽��ά������ȥ
    dataArrTwo[x][y] = weight;

}

// �и��ַ���
int split_str(char* mySendStr){
    char* p;
    int a;

    a=0;
    p=strtok(mySendStr,",");
    while(p != NULL){
        // printf("%s\n", p);
        dataArrOne[a] = p;
        p = strtok(NULL,",");
        a++;
    }
    return a;
}

