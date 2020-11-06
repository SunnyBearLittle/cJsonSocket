#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#pragma comment(lib,"..\\WS2_32.Lib")   //���� ws2_32.dll
#define maxnum  1000
#define BUF_SIZE 500
#define INFO_SIZE 15
#define DRAW_SIZE 15

char returnData[100];

int split_str(char* mySendStr);
// �洢�ֶβ�ͬ����
char* dataArrOne[INFO_SIZE];
char* dataDrawOne[DRAW_SIZE];

void sortOutPath(char* routerPathStr);
int dataArrTwo[100][100];
char* getData(char* dataStr);
char* getPrev(char* dataStr);
void save(char* drawStr, int drawCount);

int main(int argc, char* argv[])
{
	WSADATA wsaData;
	SOCKET servSock;
	SOCKADDR_IN sockAddr;
	SOCKADDR clntAddr;
	int nSize, arrSize, allSize, matrixSize,x,y;//matrixSize�����С
    char *startStr, *endStr;
    
	char buffer[BUF_SIZE];
	// �洢��ͼ�������ݶ�
	

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

    // ��ʼ��startStr��endStr
    startStr = "";
    endStr = "";
	while (1)
	{
		char* ptr;
		char* ptrData;
		int infoSize;//�������
		int x,y,a,b,index;
		float result;
		int dist[maxnum];//����·��
		int pre[maxnum];     // ��¼��ǰ���ǰһ�����
        int drawCount;
        char *routerStr;
        int drawInfoSize;

        char* equipmentName, *lanAffliation, *routerIp, *operatingSystem, *taskSystem, *area, *prev, *next;
        char* deviceBrand, *transformRate,*routerProtocol, *jumpNumber,*linkDelay,*networkLevel;
        
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);
		//send(clntSock, buffer, strLen, 0);
		char arrData[BUF_SIZE];
		memcpy(&arrData, buffer, BUF_SIZE);
		// printf("%s\n", arrData);
        // �ж����ݷ����Ƿ����,ͳ��Ԫ�ظ���
        if(strcmp("q", arrData) == 0){
            printf("���վ����������\n");
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
        }else if(strcmp("s", arrData) == 0){
            // ��ʼ������һ������
            drawCount = 0;
            startStr = "s";
            continue;
        }else if(strcmp("e", arrData) == 0){
            // ������ͼ���ݽ���
            startStr = "";
			printf("��ͼ���ݷ�����ɣ�\n");

			//����ͼ����
            // router = drawDataStrArr[0], fireWall = drawDataStrArr[1], interChanger = drawDataStrArr[2], computer1 = drawDataStrArr[4]
            printf("routerStr:%s\n", dataDrawOne[0]);
            // printf("firewall:%s\n", dataDrawOne[1]);
            // printf("interChanger:%s\n", dataDrawOne[2]);
            // printf("computer:%s\n", dataDrawOne[3]);


            // drawInfoSize = split_str(routerStr);
            // ��ȡequipmentName
            // equipmentName = getData(dataArrOne[0]);
            // printf("equipment:%s", equipmentName);
        }else{
            if(strcmp("s", startStr) == 0){
                // char* temp;
                // �洢·����������ǽ������
                // printf("�����±꣺%d\n", drawCount);
                // printf("����ǽ�����ݣ�%s\n", arrData);
                // temp = arrData;
                save(arrData, drawCount);
                // dataDrawOne[drawCount] = temp;
				// printf("�洢���ݣ�%s\n", dataDrawOne[drawCount]);
                drawCount++;
            }else {
                 // ���վ����������

                // printf("%s\n",arrData);
                infoSize = split_str(arrData);
                // printf("info_size:%d\n", infoSize);
                // printf("routerPath:%s\n", dataArrOne[8]);

                // �����ַ���Ϊ��ά��������
                sortOutPath(dataArrOne[8]);

                // ��ȡ�豸����
                // equipmentName = getData(dataArrOne[0]);
                // printf("equipment:%s", equipmentName);

                // lanAffliation  = getData(dataArrOne[1]);
                // printf("lanAffliation:%s\n", lanAffliation);
                // routerIp  = getData(dataArrOne[2]);
                // printf("routerIp:%s\n", routerIp);
                // operatingSystem  = getData(dataArrOne[3]);
                // printf("operatingSystem:%s\n", operatingSystem);
                // deviceBrand  = getData(dataArrOne[4]);
                // printf("deviceBrand:%s\n", deviceBrand);
                // transformRate  = getData(dataArrOne[5]);
                // printf("transformRate:%s\n", transformRate);
                // routerProtocol  = getData(dataArrOne[6]);
                // printf("routerProtocol:%s\n", routerProtocol);
                // jumpNumber  = getData(dataArrOne[7]);
                // printf("jumpNumber:%s\n", jumpNumber);
                // linkDelay  = getData(dataArrOne[9]);
                // printf("linkDelay:%s\n", linkDelay);
                // networkLevel  = getData(dataArrOne[10]);
                // printf("networkLevel:%s\n", networkLevel);
                // taskSystem  = getData(dataArrOne[11]);
                // printf("taskSystem:%s\n", taskSystem);
                // area  = getData(dataArrOne[12]);
                // printf("area:%s\n", area);
                // prev  = getPrev(dataArrOne[13]);
                // next  = getPrev(dataArrOne[14]);
                // printf("prev:%s\tnext:%s\n", prev, next);


                arrSize++;
            }
        }
        
	}
	//�ر��׽���
	closesocket(servSock);
	//��ֹ DLL ��ʹ��
	WSACleanup();
	return 0;
}

//���浽һά������
void save(char* drawStr, int drawCount){
    char* p;
    p = malloc(strlen(drawStr));
    if (p == NULL) {
		exit(1);
	}
    strcpy(p, drawStr);

    dataDrawOne[drawCount] = p;
}

//��ȡprev��next
char* getPrev(char* dataStr){
    
    char* p;
    // returnData = (char*)malloc(100);
    p=strtok(dataStr,":");
    p = strtok(NULL,":");
    // printf("��ȡ�ĺ������ݣ�%s\t", p);

    // ȥ��������
    p = strtok(p, "[");
    // printf("ȥ��һ�������ţ�%s\t", p);

    p = strtok(p, "]");
    // printf("ȥ��һ�������ţ�%s\t", p);

    // ȥ��������
    p = strtok(p, "'");
    p = strtok(p, "'");
    // printf("%s\t",p);

    // strcpy(returnData,p);
    // printf("strcpy:%s\n", returnData);

    return p;
}

// ��ȡ�豸����
char* getData(char* dataStr){
    char* p;
    p=strtok(dataStr,":");
    p = strtok(NULL,":");
    // ȥ��������
    p = strtok(p, "'");
    p = strtok(p, "'");
    printf("%s\n",p);
    return p;
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
    
    // printf("%s\n",p);
    

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

