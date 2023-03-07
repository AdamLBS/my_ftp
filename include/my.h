/*
** EPITECH PROJECT, 2023
** B-NWP-400-MAR-4-1-myftp-adam.elaoumari
** File description:
** my
*/
#ifndef MY_H_
    #define MY_H_
    #include <sys/socket.h>
    #include <sys/un.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <sys/select.h>
    #include <stdbool.h>
    #include <stdlib.h>
    #include <stdio.h>
    #include <string.h>
    #include <fcntl.h>
    #include <strings.h>
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>
    #include <dirent.h>
    #include <sys/sendfile.h>
    #define MSGOKAY  "200 Command okay.\r\n"
    #define FILEOKAY "150 File status okay; about to open data connection.\r\n"
    #define CLOSEDATA "226 Closing data connection.\r\n"
    #define NODATA "425 Use PORT or PASV first.\r\n"
    #define LOGOUTMSG "221 Service closing control connection.\r\n"
    #define FILEACTION "250 Requested file action okay, completed.\r\n"
    #define USERLOGGED "230 User logged in, proceed.\r\n"
    #define NEEDACCOUNT "332 Need account for login.\r\n"
    #define UNKNOWN "500 Unknown command.\r\n"
    #define QUITMSG "221 Service closing control connection.\r\n"
    #define WRONGUSRMSG "530 Wrong USER.\r\n"
    #define HELPMSG "214 Help message.\r\n"
    #define ERRORCWD "550 Failed to change directory.\r\n"
    #define ERRORDEL "550 No file name.\r\n"
    #define PORTERR "425 Can't open data connection.\r\n"
    #define PORTOKAY "200 Command okay.\r\n"
    #define TYPEOKAY "200 Switching to Binary mode.\r\n"
    #define _GNU_SOURCE
    struct clients {
        int data_fd;
        int control_fd;
        int data_port;
        int original_data_fd;
        bool connected;
        char *user;
        char *pass;
        char *old_pwd;
        char *pwd;
        char *buffer;
        char *data_buffer;
        bool check_read;
        FILE *readfd;
        bool pasv;
        int activ_port;
        char *activ_ip;
    } typedef t_clients;


    struct serverinfo {
        char *serverpath;
        int port;
    } typedef t_server;

    int create_server(t_server *server);
    void loop_server(int serversocket, t_clients *clients, t_server *server);
    void add_client(t_clients *clients, bool data, int fd);
    void add_clients_to_set(fd_set *rfds, t_clients *clients);
    void read_clients_control(fd_set *rfds, t_clients *clients);
    char *my_itoa(int val, char *buffer);
    void send_pasv_info(char *adress, int port, int fd);
    int create_data(struct sockaddr_in *adress, int clienFd);
    char *my_revstr(char *src);
    void add_data_port_to_client(t_clients *clients, int clientfd);
    void read_clients_data(fd_set *rfds, t_clients *clients);
    void do_retr_cmd(int index, t_clients *clients, char *buf);
    int is_client_logged_in(int index, t_clients *clients);
    void handle_client_control(int index, t_clients *clients);
    void do_user_cmd(int index, t_clients *clients, char *buf);
    void do_pass_cmd(int index, t_clients *clients, char *buf);
    int is_login_or_pass(char *buf);
    void send_file_to_data(int index, t_clients *clients, char *path, FILE *fd);
    void clear_client_data(int index, t_clients *clients);
    void do_noop(int index, t_clients *clients);
    int my_getnbr(char *str);
    int my_getnbr_pos(char *str, int i);
    void check_cmds(int index, t_clients *clients, char *buf);
    void do_logout(int index, t_clients *clients);
    void do_pwd(int index, t_clients *clients);
    void do_list(int index, t_clients *clients);
    int does_client_has_data(int index, t_clients *clients);
    void read_sockets(fd_set *rfds, t_clients *clients, int selectqueue);
    int check_server_connections(int serversocket, fd_set *rfds,
    t_clients *clients, int *selectqueue);
    int check_data_connections(fd_set *rfds, t_clients *clients,
    int *selectqueue);
    void send_list_data(char *dirlist, int index, t_clients *clients);
    void check_if_client_closed(int index, t_clients *clients, int val);
    int help_message(int ac, char **av);
    void do_unknown_cmd(int index, t_clients *clients);
    void check_cmds2(int index, t_clients *clients, char *buf);
    void do_quit_cmd(int index, t_clients *clients);
    void do_help_cmd(int index, t_clients *clients);
    int check_cmds_nologin(int index, t_clients *clients, char *buf);
    void initialize_clients(t_clients *clients, t_server *server);
    void do_cwd_cmd(int index, t_clients *clients, char *buf);
    void do_change_directory(char *dir, int index, t_clients *clients);
    void check_cmds3(int index, t_clients *clients, char *buf);
    void do_cdup(int index, t_clients *clients);
    int is_buffer_ended(int index, t_clients *clients);
    void clear_buffer(int index, t_clients *clients);
    void create_buffer(int index, t_clients *clients);
    void do_delete(char *file, int index, t_clients *clients);
    void do_delete_cmd(int index, t_clients *clients, char *buf);
    void do_stor_cmd(int index, t_clients *clients, char *buf);
    void upload_data_to_file(int index, t_clients *clients, char *path);
    void handling_data_socket(int index, t_clients *clients);
    void do_list_with_params(int index, t_clients *clients, char *buf);
    void exec_list_params(int index, t_clients *clients, char *val);
    void do_port_cmd(int index, t_clients *clients, char *buf);
    void my_put_nbr(int nb);
    void my_putchar(char c);
    char **split_args(char *buf);
    int check_port_connection(t_clients *clients, int index,
        struct sockaddr_in data_addr, char *str);
    int my_arrlen(char **arr);
    void check_cmds4(int index, t_clients *clients, char *buf);
    int get_port(char *port1, char *port2);
    char *get_client_ip(char **parsed);
    void free_port_val(char *ip, char **parsed);
    void accept_data(int index, t_clients *clients);
    int check_dir(char *path);
#endif /* !MY_H_ */
