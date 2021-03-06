#ifndef TCPHIJACK_H
#define TCPHIJACK_H

void fill_packet(   char *srcIP,
                    char *dstIP,
                    u_int16_t dstPort,
                    u_int16_t srcPort,
                    u_int32_t syn,
                    u_int16_t ack,
                    u_int32_t seq,
                    u_int32_t ack_seq,
                    u_int16_t rst,
                    const char * data,
                    char *packet,
                    uint32_t packet_size);

char* gen_packet(   char *srcIP,
                    char *dstIP,
                    u_int16_t dstPort,
                    u_int16_t srcPort,
                    u_int32_t syn,
                    u_int16_t ack,
                    u_int32_t seq,
                    u_int32_t ack_seq,
                    const char * data,
                    uint32_t packet_size);

bool seq_flood(     char *srcIP,
                    char *dstIP,
                    u_int16_t dstPort,
                    u_int16_t srcPort,
                    u_int32_t seq,
                    u_int32_t ack_seq,
                    int n,
                    int socket_fd,
                    struct sockaddr_in addr_in);


int send_packet(int socket_fd, char *packet, struct sockaddr_in addr_in);
void print_packet_bits(char *packet, int packet_size);
void print_packet_ascii(char *packet, int packet_size);

//Calculate the TCP header checksum of a string (as specified in rfc793)
//Function from http://www.binarytides.com/raw-sockets-c-code-on-linux/
unsigned short csum(unsigned short *ptr,int nbytes);

//Pseudo header needed for calculating the TCP header checksum
struct pseudoTCPPacket {
  uint32_t srcAddr;
  uint32_t dstAddr;
  uint8_t zero;
  uint8_t protocol;
  uint16_t TCP_len;
};


#endif