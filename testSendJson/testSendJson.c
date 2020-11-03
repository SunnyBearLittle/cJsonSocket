#include <stdio.h>
#include <WinSock2.h>
#include <windows.h>
#include <math.h>
#include <string.h>
#include <conio.h>
#include <time.h>
#pragma comment(lib,"..\\WS2_32.Lib")  //���� ws2_32.dll
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

    //��ʼ��DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	memset(&sockAddr, 0, sizeof(sockAddr));  //ÿ���ֽڶ���0���
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);

    arr_num = 0;


    while(1){
        int count;
		char* mySendStr;
		int i,j,size;
		int num;

        if( arr_num == 2 ) arr_num = 0;

		count = 0;

        if(str[arr_num] == "top"){
			//1. ͳ��Ԫ�ظ���
			for ( i = 0; i < sizeof(top) / sizeof(top[0]); i++)
			{
				for ( j = 0; j < sizeof(top) / sizeof(top[0]); j++)
				{
					count++;
				}
			}

            // 2.������
            size = (int)(sqrt(count));

            // 3. ���ɷ�������
            for(i=0; i< size; i++){
                for(j=0; j< size; j++){
                    Sleep(500);
                    mySendStr = "";
                    mySendStr = generateSendStr(i,j, top[i][j]);
                    // printf("mySendStr:%s\n", mySendStr);
                    printf("===================�ָ���=====================\n");
                    
                    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
                    num = send(sock, mySendStr, BUF_SIZE, 0);
                    split_str(mySendStr);
                    if (num < 0) {
                        perror("send error!");
                        exit(1);
                    }

                    memset(bufSend, 0, BUF_SIZE);  //���û�����
                    memset(bufRecv, 0, BUF_SIZE);  //���û�����
                }
            }
        }else if(str[arr_num] == "tree"){
            //1. ͳ��Ԫ�ظ���
			for ( i = 0; i < sizeof(tree) / sizeof(tree[0]); i++)
			{
				for ( j = 0; j < sizeof(tree) / sizeof(tree[0]); j++)
				{
					count++;
				}
			}

            // 2.������
            size = (int)(sqrt(count));

            // 3. ���ɷ�������
            for(i=0; i< size; i++){
                for(j=0; j< size; j++){
                    Sleep(500);
                    mySendStr = "";
                    mySendStr = generateSendStr(i,j, tree[i][j]);
                    // printf("mySendStr:%s\n", mySendStr);
                    printf("===================�ָ���=====================\n\n");
                    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
			        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
                    
                    num = send(sock, mySendStr, BUF_SIZE, 0);
                    split_str(mySendStr);
                    if (num < 0) {
                        perror("send error!");
                        exit(1);
                    }

                    memset(bufSend, 0, BUF_SIZE);  //���û�����
                    memset(bufRecv, 0, BUF_SIZE);  //���û�����
                }
            }
        }

        sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
        connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
        
        // ���ݷ��ͽ���֮�󣬷���һ���ַ�q��ʾ���ݴ������
        num = send(sock, "q", BUF_SIZE, 0);
        if (num < 0) {
            perror("send error!");
            exit(1);
        }

        memset(bufSend, 0, BUF_SIZE);  //���û�����
        memset(bufRecv, 0, BUF_SIZE);  //���û�����

        arr_num++;
    }
	
    closesocket(sock);  //�ر��׽���
	WSACleanup();  //��ֹʹ�� DLL
	return 0;
}

// ���ɷ�������
char* generateSendStr(int from, int to, int weight){
    char *router = "'equipmentName':'·����1','lanAffliation':'������1',";
    char *joinIp = randIp();
    char* mySendStr;
    char* routerPathStr = generatePath(from, to, weight);
    
    char* others1 = ",'operatingSystem':'Windows 7','deviceBrand':'˼��','transformRate':'25Mbps','routerProtocol':'Э��','jumpNumber':'8',";
    char* others2 = ",'linkDelay':'20ms','networkLevel':'�Ǹ���','taskSystem':'����ϵͳ','area':'ӡ���µ���','prev':['·����2\'],'next':['����ǽ']";

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

// ·������
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


// �������IP

char* randIp(){
    int a;
    char ip4[120];

    char *joinIp = "'routerIp':'192.168.1.";
    
    // �������IP 1-255
    srand((unsigned)time(NULL));
    a = rand() % 255 + 1;
    // printf("���ɵ��������%d\n", a);

    sprintf(ip4,"%d", a);
    joinIp = join(joinIp, ip4);
    joinIp = join(joinIp, "'");
    // printf("joinIp:%s\n",joinIp);

    return joinIp;
}


// �и��ַ���
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


//ƴ�ӳ��ַ��� 

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
