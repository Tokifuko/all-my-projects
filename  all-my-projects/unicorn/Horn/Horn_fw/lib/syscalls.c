/*������ �������� ��� ARM �� GCC (Code Sourcery Lite � ��� �����) ������������ ������ � newlib � ����������� ����������� ����� C. � ������� �� ����� ������������ ��������� ������� ����������� ������� (printf/scanf/malloc � �.�.).
��� ���� ����� ������������ ��� ���������� �� ��� ��������� ���������� ��������� ��������� �������.
��� ������� � ����������� � ������� ������������ ���������� ��� stm32. stdout/stderr ������������ � USART1, stdin � �� USART1.
*/
//http://we.easyelectronics.ru/STM32/ispolzuem-libc-newlib-dlya-stm32.html

#include <errno.h>
#include <sys/stat.h>
#include <sys/times.h>
#include <sys/unistd.h>
#include <stm32f10x.h>

extern uint32_t __get_MSP(void);

#define STDOUT_USART USART2
#define STDERR_USART USART2
#define STDIN_USART USART2

// errno
#undef errno
extern int errno;

/*
 ���������� ����� - ������ ������.
 */
char *__env[1] = { 0 };
char **environ = __env;

int _write(int file, char *ptr, int len);

// exit - ���������� �����. � �������� ������ - �������������.
void _exit(int status)
{
    while (1);
}

// close - �������� ����� - ���������� ������
int _close(int file)
{
    return -1;
}
/*
 execve - �������� ���������� ������ �������� - ��������� ��� -> ���������� ������.
 */
int _execve(char *name, char **argv, char **env)
{
    errno = ENOMEM;
    return -1;
}

/*
 fork = �������� ������ ��������
 */
int _fork()
{
    errno = EAGAIN;
    return -1;
}

/*
 fstat - ��������� ��������� �����
 */
int _fstat(int file, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 getpid - �������� ID �������� ��������
 */

int _getpid()
{
    return 1;
}

/*
 isatty - �������� �� ���� ����������.
 */
int _isatty(int file)
{
    switch (file)
    {
    case STDOUT_FILENO:
    case STDERR_FILENO:
    case STDIN_FILENO:
        return 1;
    default:
        //errno = ENOTTY;
        errno = EBADF;
        return 0;
    }
}

/*
 kill - ������� ������ ��������
 */
int _kill(int pid, int sig)
{
    errno = EINVAL;
    return (-1);
}

/*
 link - ��������� ����� ��� ��� ������������� �����.
 */

int _link(char *old, char *new)
{
    errno = EMLINK;
    return -1;
}

/*
 lseek - ���������� ������� � �����
 */
int _lseek(int file, int ptr, int dir)
{
    return 0;
}

/*
 sbrk - ��������� ������ ������� ������, ����������� ��� malloc
 */
caddr_t _sbrk(int incr)
{
    extern char _ebss;
    static char *heap_end;
    char *prev_heap_end;

    if (heap_end == 0)
    {
        heap_end = &_ebss;
    }
    prev_heap_end = heap_end;

    char * stack = (char*) __get_MSP();
    if (heap_end + incr > stack)
    {
        _write(STDERR_FILENO, "Heap and stack collision\n", 25);
        errno = ENOMEM;
        return (caddr_t) -1;
        //abort ();
    }

    heap_end += incr;
    return (caddr_t) prev_heap_end;

}

/*
 read - ������ �� �����, � ��� ���� ��� ������ ���� ������ stdin
 */

int _read(int file, char *ptr, int len)
{
    int n;
    int num = 0;
    switch (file)
    {
    case STDIN_FILENO:
        for (n = 0; n < len; n++)
        {
            while (USART_GetFlagStatus(STDIN_USART, USART_FLAG_RXNE) == RESET);
            char c = (char) (USART_ReceiveData(STDIN_USART) & (uint16_t) 0x01FF);
            *ptr++ = c;
            num++;
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return num;
}

/*
 stat - ��������� ��������� �����.
 */

int _stat(const char *filepath, struct stat *st)
{
    st->st_mode = S_IFCHR;
    return 0;
}

/*
 times - ��������� ���������� � �������� (������� �����: ���������, ������������ � �.�.)
 */

clock_t _times(struct tms *buf)
{
    return -1;
}

/*
 unlink - ������� ��� �����.
 */
int _unlink(char *name)
{
    errno = ENOENT;
    return -1;
}

/*
 wait - �������� �������� ���������
 */
int _wait(int *status)
{
    errno = ECHILD;
    return -1;
}

/*
 write - ������ � ���� - � ��� ���� ������ stderr/stdout
 */
int _write(int file, char *ptr, int len)
{
    int n;
    switch (file)
    {
    case STDOUT_FILENO: /*stdout*/
        for (n = 0; n < len; n++)
        {
            while (USART_GetFlagStatus(STDOUT_USART, USART_FLAG_TC) == RESET);
            USART_SendData(STDOUT_USART, (uint8_t) * ptr++);
        }
        break;
    case STDERR_FILENO: /* stderr */
        for (n = 0; n < len; n++)
        {
            while (USART_GetFlagStatus(STDERR_USART, USART_FLAG_TC) == RESET);
            USART_SendData(STDERR_USART, (uint8_t) * ptr++);
        }
        break;
    default:
        errno = EBADF;
        return -1;
    }
    return len;
}
