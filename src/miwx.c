#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define REQU_SIZE 1024
#define PATH_SIZE 256

char *head = "HTTP/1.1 200 OK\r\n\r\n";
char *nfound = "HTTP/1.1 404 Not Found\r\n\r\n<html>\n<head>\n<title>miwx - 404</title>\n</head>\n<body>\n<h1>Not Found</h1>\n<hr>\n<address>miwx-web-server</address>\n</head>\n</html>";

int p, sfd, cfd;
struct sockaddr_in sa, ca;
socklen_t cal;

int fsize, scount;
char rbuf[REQU_SIZE], fpath[PATH_SIZE];
char *fbuf, *resp;
size_t len;
FILE *fp;

int err(char *content){
	printf("ERROR: %s\n", content);
	return 0;
}

void cpy(char *dest, char *src){
	for (int i = 0; i < strlen(src); i++){
		dest[i] = src[i];
	}
}

int main(int argc, char *argv[]){
	if (geteuid() != 0){
		return err("Start without root privileges");
	}else if (argc < 2){
		return err("No port determined -> Usage: miwx [port]");
	}
	
	p = atoi(argv[1]);

	if ((sfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		return err("Couldn't create socket");
	}

	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = INADDR_ANY;
	sa.sin_port = htons(p);

	if (bind(sfd, (struct sockaddr *) &sa, sizeof(sa)) < 0){
		return err("Couldn't bind socket");
	}

	if (listen(sfd, 5) < 0){
		return err("Listening to connections not possible");
	}

	for (;;){
		cal = sizeof(ca);
		if ((cfd = accept(sfd, (struct sockaddr *) &ca, &cal)) < 0){
			err("Couldn't fetch connection to client");
			continue;
		}

		memset(rbuf, 0, sizeof(char) * REQU_SIZE);
		if (read(cfd, rbuf, REQU_SIZE - 1) < 0){
			err("Couldn't read from client");
			continue;
		}
		memset(fpath, 0, sizeof(char) * PATH_SIZE);
		scount = 0;
		for (int i = 0; i < strlen(rbuf); i++){
			if (rbuf[i] == ' '){
				scount += 1;
				if (scount > 1)
					break;
			}
			if (scount == 1){
				fpath[strlen(fpath)] = rbuf[i];
			}
		}
		fpath[0] = '.';
		if (strcmp(fpath, "./") == 0){
			strcat(fpath, "index.html");
		}
		printf("%s:%d -> %s:%d | %s\n", inet_ntoa(ca.sin_addr), ntohs(ca.sin_port), inet_ntoa(sa.sin_addr), ntohs(sa.sin_port), fpath);

		if ((fp = fopen(fpath, "rb")) != NULL){
			fseek(fp, 0, SEEK_END);
			fsize = ftell(fp);
			fseek(fp, 0, SEEK_SET);
			fbuf = malloc(fsize);
			len = fread(fbuf, sizeof(char), fsize, fp);
			if (ferror(fp) != 0){
				resp = malloc(sizeof(char) * strlen(nfound));
				cpy(resp, nfound);
			}else{
				fbuf[len++] = '\0';
				fclose(fp);
				resp = malloc(sizeof(char) * (strlen(head) + strlen(fbuf)));
				cpy(resp, head);
				strcat(resp, fbuf);
			}
		}else{
			resp = malloc(sizeof(char) * strlen(nfound));
			cpy(resp, nfound);
		}

		if (write(cfd, resp, strlen(resp)) < 0){
			err("Couldn't send response to client");
			continue;
		}
		close(cfd);
	}
	close(sfd);
	return 0;
}
