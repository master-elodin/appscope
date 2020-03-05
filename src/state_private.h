#ifndef __STATE_PRIVATE_H__
#define __STATE_PRIVATE_H__

#include <limits.h>
#include <sys/socket.h>

#define PROTOCOL_STR 16
#define SCOPE_UNIX 99

//
// This file contains implementation details for state.c and reporting.c.
// It is expected that state.c and report.c will both directly include
// this file, but it is not recommended that any other file include it.
//

typedef struct metric_counters_t {
    uint64_t openPorts;
    uint64_t netConnectionsUdp;
    uint64_t netConnectionsTcp;
    uint64_t netConnectionsOther;
    uint64_t netrxBytes;
    uint64_t nettxBytes;
    uint64_t readBytes;
    uint64_t writeBytes;
    uint64_t numSeek;
    uint64_t numStat;
    uint64_t numOpen;
    uint64_t numClose;
    uint64_t numDNS;
    uint64_t fsDurationNum;
    uint64_t fsDurationTotal;
    uint64_t connDurationNum;
    uint64_t connDurationTotal;
    uint64_t dnsDurationNum;
    uint64_t dnsDurationTotal;
    uint64_t netConnectErrors;
    uint64_t netTxRxErrors;
    uint64_t netDNSErrors;
    uint64_t fsOpenCloseErrors;
    uint64_t fsRdWrErrors;
    uint64_t fsStatErrors;
} metric_counters;

typedef struct {
    struct {
        int open_close;
        int read_write;
        int stat;
        int seek;
        int error;
    } fs;
    struct {
        int open_close;
        int rx_tx;
        int dns;
        int error;
        int dnserror;
    } net;
} summary_t;

typedef struct net_info_t {
    int active;
    int type;
    bool urlRedirect;
    uint64_t numTX;
    uint64_t numRX;
    uint64_t txBytes;
    uint64_t rxBytes;
    bool dnsSend;
    uint64_t startTime;
    uint64_t numDuration;
    uint64_t totalDuration;
    uint64_t uid;
    uint64_t lnode;
    uint64_t rnode;
    char dnsName[MAX_HOSTNAME];
    struct sockaddr_storage localConn;
    struct sockaddr_storage remoteConn;
} net_info;

typedef struct fs_info_t {
    int active;
    fs_type_t type;
    uint64_t numOpen;
    uint64_t numClose;
    uint64_t numSeek;
    uint64_t numRead;
    uint64_t numWrite;
    uint64_t readBytes;
    uint64_t writeBytes;
    uint64_t numDuration;
    uint64_t totalDuration;
    uint64_t uid;
    char path[PATH_MAX];
} fs_info;



// Accessor functions defined in state.c, but used in report.c too.
int get_port(int fd, int type, control_type_t which);
bool checkNetEntry(int fd);
bool checkFSEntry(int fd);
net_info* getNetEntry(int fd);
fs_info* getFSEntry(int fd);


// Data that lives in state.c, but is used in report.c too.
extern summary_t g_summary;
extern net_info *g_netinfo;
extern fs_info *g_fsinfo;
extern metric_counters g_ctrs;

#endif // __STATE_PRIVATE_H__