#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#pragma comment(lib,"..\\WS2_32.Lib")  //加载 ws2_32.dll
#define BUF_SIZE 500
#pragma warning(disable:4996)

char* join(char* a, char* b);
void split_str(char* mySendStr);
char* randIp();
char* generatePath(int from, int to, int weight);
char* generateSendStr(int from, int to, int weight);


int main()
{

    SOCKADDR_IN sockAddr;
	char bufSend[BUF_SIZE];
	char bufRecv[BUF_SIZE];
	SOCKET sock;
	int arr_num;
	int top[5][5] = {
						{9999,10,9999,30,100},
						{10,9999,50,9999,9999},
						{9999,50,9999,20,10},
						{30,9999,20,9999,40},
						{100,9999,10,40,9999}
					};

	int net[5][5] = {
						{9999,1,2,3,4},
						{1,9999,5,2,3},
						{2,5,9999,4,1},
						{3,2,4,9999,2},
						{4,3,1,2,9999}
					};
	
	
	int tree[6][6] = {
						{9999,1,2,3,9999,9999},
						{1,9999,9999,9999,4,5},
						{2,9999,9999,9999,9999,9999},
						{3,9999,9999,9999,9999,9999},
						{9999,4,9999,9999,9999,9999},
						{9999,5,9999,9999,9999,9999}
					};

	int star[5][5] = {
						{9999,2,3,4,5},
						{2,9999,9999,9999,9999},
						{3,9999,9999,9999,9999},
						{4,9999,9999,9999,9999},
						{5,9999,9999,9999,9999}
					};


    char *str[4] = { "top", "tree"};

    //初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

    arr_num = 0;


    while(1){
        int count;
		char* mySendStr;
		int i,j,size;
		int num;
        char *router1, *fireWall1, *interChanger1, *computer1;

        if( arr_num == 2 ) arr_num = 0;

		count = 0;
        printf("数据发送中...\n");
        if(str[arr_num] == "top"){
			//1. 统计元素个数
			for ( i = 0; i < sizeof(top) / sizeof(top[0]); i++)
			{
				for ( j = 0; j < sizeof(top) / sizeof(top[0]); j++)
				{
					count++;
				}
			}

            // 2.矩阵规格
            size = (int)(sqrt(count));

            // 3. 生成发送数据
            for(i=0; i< size; i++){
                for(j=0; j< size; j++){
                    Sleep(500);
                    mySendStr = "";
                    mySendStr = generateSendStr(i,j, top[i][j]);
                    // printf("mySendStr:%s\n", mySendStr);
                    //printf("===================分割线=====================\n");
                    
                    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
                    num = send(sock, mySendStr, BUF_SIZE, 0);
                    // 矩阵数据不进行展示
                    // split_str(mySendStr);
                    if (num < 0) {
                        perror("send error!");
                        exit(1);
                    }

                    memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
                    memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区
                }
            }
        }else if(str[arr_num] == "tree"){
            //1. 统计元素个数
			for ( i = 0; i < sizeof(tree) / sizeof(tree[0]); i++)
			{
				for ( j = 0; j < sizeof(tree) / sizeof(tree[0]); j++)
				{
					count++;
				}
			}

            // 2.矩阵规格
            size = (int)(sqrt(count));

            // 3. 生成发送数据
            for(i=0; i< size; i++){
                for(j=0; j< size; j++){
                    Sleep(500);
                    mySendStr = "";
                    mySendStr = generateSendStr(i,j, tree[i][j]);
                    // printf("mySendStr:%s\n", mySendStr);
                   // printf("===================分割线=====================\n\n");
                    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
                    
                    num = send(sock, mySendStr, BUF_SIZE, 0);
                    // split_str(mySendStr);
                    if (num < 0) {
                        perror("send error!");
                        exit(1);
                    }

                    memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
                    memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区
                }
            }
        }

        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        
        // 数据发送结束之后，发送一个字符q表示数据传输完成
        num = send(sock, "q", BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区

        // 画图数据发送开始标记
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        num = send(sock, "s", BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区

        // 发送画图数据
        router1 = "'equipmentName': '路由器1', 'deviceType':'路由器','lanAffiliation': '局域网1','routerIp': '192.168.1.1','operatingSystem': 'Windows 7','deviceBrand': '思科','transformRate': '25Mbps','routerProtocol':'协议', 'jumpNumber':'8','routerPath':'路径','linkDelay':'20ms','networkLevel': '骨干网','taskSystem': '军事系统','area': '印度新德里','prev':[],'next':['防火墙1']"; 
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        num = send(sock, router1, BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }
        Sleep(500);

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区
        
        fireWall1 = "'equipmentName': '防火墙1', 'deviceType':'防火墙','lanAffiliation': '局域网1','safeStrategy': '安全策略','networkLevel':'核心网', 'taskSystem':'军事系统','area': '印度新德里','prev':['路由器1'],'next':['交换机1']";
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        num = send(sock, fireWall1, BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }
        Sleep(500);

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区
        
        interChanger1 = "'equipmentName': '交换机1','interchangerIp':'192.168.1.1','lanAffiliation': '局域网1','deviceType': '交换机','operatingSystem': 'IOS','deviceBrand': '思科', 'interchangerProtocol': 'STP','transformRate': '100Mbps', 'handlingCapacity': '50Mbps','linkDelay': '1ms','livePort': '8','gateway': '192.168.1.1','networkLevel': '核心网', 'area': '印度新德里','taskSystem': '军事系统','prev':['防火墙1'],'next':['主机1']";
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        num = send(sock, interChanger1, BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }
        Sleep(500);

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区

        computer1 = "'equipmentName': '主机1', 'lanAffiliation': '局域网1','hostIp': '192.168.1.1','deviceType': '主机','operatingSystem': 'Windows 7','deviceBrand': '思科','hostProtocol': 'HTTP','handlingCapacity': '50Mbps','linkDelay': '1ms','livePort': '8','gateway': '192.168.1.200','area': '印度新德里','networkLevel': '核心网','taskSystem': '军事系统1数据','prev':['交换机1'],'next':[]";
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        printf("发送的computer：%s\n", computer1);
		num = send(sock, computer1, BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }
        Sleep(500);

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区

        // 画图数据结束标记
        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        num = send(sock, "e", BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }

        memset(bufSend, 0, BUF_SIZE);  //重置缓冲区
        memset(bufRecv, 0, BUF_SIZE);  //重置缓冲区

        arr_num++;
    }
	
    closesocket(sock);  //关闭套接字
	WSACleanup();  //终止使用 DLL
	return 0;
}

// 生成发送数据
char* generateSendStr(int from, int to, int weight){
    char *router = "'equipmentName':'路由器1','lanAffliation':'局域网1',";
    char *joinIp = randIp();
    char* mySendStr;
    char* routerPathStr = generatePath(from, to, weight);
    
    char* others1 = ",'operatingSystem':'Windows 7','deviceBrand':'思科','transformRate':'25Mbps','routerProtocol':'协议','jumpNumber':'8',";
    char* others2 = ",'linkDelay':'20ms','networkLevel':'骨干网','taskSystem':'军事系统','area':'印度新德里','prev':['路由器2\'],'next':['防火墙']";

    // printf("routerPathStr:%s\n", routerPathStr);
    mySendStr = "";
    mySendStr = join(mySendStr, router);
    mySendStr = join(mySendStr,joinIp);
    mySendStr = join(mySendStr, others1);
    mySendStr = join(mySendStr, routerPathStr);
    mySendStr = join(mySendStr, others2);

    // printf("mysendStr:\n");
    // printf("%s", mySendStr);

    return mySendStr;
}

// 生成lanAffliation
char* generateLanAffliation(){
    char* lanStr = "局域网";
    int a;
    char lanBuff[120];
    // 随机数1-5
    srand((unsigned)time(NULL));
    a = rand() % 5 + 1;

    sprintf(lanBuff, "%d", a);
    lanStr = join(lanStr, lanBuff);
    return lanStr;
}

// 生成设备名称
char* generateEquipment(){
    char* equipmentStr;
    int a;
    char* selectEquipment[] = {"路由器", "防火墙", "交换机1","交换机2","集线器"};

    // 随机数1-5
    srand((unsigned)time(NULL));
    a = rand() % 5 + 1;
	printf("%d\n", a);
    equipmentStr = selectEquipment[a];
    
    return equipmentStr;
}

// 路径生成
char* generatePath(int from, int to, int weight){
    char* routerPathStr;
    char fromStr[120];
    char toStr[120];
    char weightStr[120];
    char* s = "-";
    
    // printf("from:%d\tto:%d\n",from, to);

    routerPathStr = "'routerPath':'";
    
    sprintf(fromStr, "%d", from);
    sprintf(toStr, "%d", to);
    sprintf(weightStr, "%d", weight);


    routerPathStr = join(routerPathStr, fromStr);
    routerPathStr = join(routerPathStr, s);
    routerPathStr = join(routerPathStr, toStr);
    routerPathStr = join(routerPathStr, s);
    routerPathStr = join(routerPathStr, weightStr);
    routerPathStr = join(routerPathStr,"'");
    
    // printf("routerPathStr:%s\n", routerPathStr);

    return routerPathStr;

}


// 随机生成IP
char* randIp(){
    int a;
    char ip4[120];

    char *joinIp = "'routerIp':'192.168.1.";
    
    // 生成随机IP 1-255
    srand((unsigned)time(NULL));
    a = rand() % 255 + 1;
    // printf("生成的随机数：%d\n", a);

    sprintf(ip4,"%d", a);
    joinIp = join(joinIp, ip4);
    joinIp = join(joinIp, "'");
    // printf("joinIp:%s\n",joinIp);

    return joinIp;
}


// 切割字符串
void split_str(char* mySendStr){
    char* p;
	printf("{\n");
	p=strtok(mySendStr,",");
    while(p != NULL){
        printf("\t%s,\n", p);
        p = strtok(NULL,",");
    }
    
    printf("}\n");
}


//拼接成字符串 

char* join(char* a, char* b) {
	char* result;
	result = malloc(strlen(a) + strlen(b));
	if (result == NULL) {
		exit(1);
	}
	strcpy(result, a);
	strcat(result, b);
	return result;
}
