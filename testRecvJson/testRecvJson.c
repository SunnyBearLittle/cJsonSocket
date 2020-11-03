#include <stdio.h>
#include <winsock2.h>
#include <math.h>
#include <stdlib.h>
#pragma comment(lib,"..\\WS2_32.Lib")   //加载 ws2_32.dll
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
	int nSize, arrSize, allSize, matrixSize,x,y;//matrixSize矩阵大小
	char buffer[BUF_SIZE];

	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	servSock = socket(AF_INET, SOCK_STREAM, 0);
	//绑定套接字
	
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(1234);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//进入监听状态
	listen(servSock, 20);
	
	nSize = sizeof(SOCKADDR);
    arrSize = 0;
	while (1)
	{
		char* ptr;
		char* ptrData;
		int infoSize;//矩阵规则
		int x,y,a,b,index;
		float result;
		int dist[maxnum];//保存路径
		int pre[maxnum];     // 记录当前点的前一个结点
		SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
		int strLen = recv(clntSock, buffer, BUF_SIZE, 0);
		//send(clntSock, buffer, strLen, 0);
		char arrData[BUF_SIZE];
		memcpy(&arrData, buffer, BUF_SIZE);
        // 判断数据发送是否结束,统计元素个数
        if(strcmp("q", arrData) == 0){
            printf("数据发送完成\n");
            // 将元素数量重置为0
            allSize = arrSize;

            // 遍历二维数组
            // 1. 求二维数组大小
            matrixSize = sqrt(allSize);
            printf("矩阵大小是：%dx%d\n", matrixSize, matrixSize);

            // 2. 遍历矩阵
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

            // 整理字符串为二维数组数据
            sortOutPath(dataArrOne[8]);
            arrSize++;
        }
        
	}
	//关闭套接字
	closesocket(servSock);
	//终止 DLL 的使用
	WSACleanup();
	return 0;
}

// 清理路径数据
void sortOutPath(char* routerPathStr){
    char* p;
    int x,y, weight;
    p=strtok(routerPathStr,":");
    p = strtok(NULL,":");

    // 去除上引号
    p = strtok(p, "'");
    p = strtok(p, "'");
    
    printf("%s\n",p);
    

    // 去除-号
    p = strtok(p, "-");
    // printf("x:%s\t",p);
    // 将字符串转成数字
    x = atoi(p);
    p = strtok(NULL,"-");
    // printf("y:%s\t",p);
    y = atoi(p);
    p = strtok(NULL,"-");
    // printf("weight:%s\n",p);
    weight = atoi(p);
    
    // 将数据存到二维数组中去
    dataArrTwo[x][y] = weight;

}

// 切割字符串
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

