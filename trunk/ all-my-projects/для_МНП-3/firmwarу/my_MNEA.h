#ifndef _MY_MNEA_H
#define	_MY_MNEA_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _MY_MNEA_H */


// состояния принимающего автомата
#define MNP_WAIT_START                  0
#define MNP_GET_CRC_H                   1
#define MNP_GET_CRC_L                   2
#define MNP_GET_CR                      3
#define MNP_GET_LF                      4
#define MNP_WAIT_CRC_L                  5
#define MNP_GET_DATA                    6


// размер буфера для сообщений
#define	 MNP_MESSAGE_BUFFER_SIZE        128

//коды ошибок принимающего автомата
#define ERR_RX_EMPTY                            -1 // буфер пустой
#define ERR_RX_OVERFLOW                         -2 //переполнение приемного буфера
#define ERR_MNP_MESSAGE_OVERFLOW                -3 //переполнение буфера сообщения
#define ERR_MNP_START_EXPECTED                  -4 // ожидалось начало пакета, а пришло что-то другое
#define ERR_MNP_START_UNEXPECTED                -5 // неожиданное начало нового сообщения
#define ERR_MNP_END_UNEXPECTED                  -6 // неожиданный конец сообщения.
#define ERR_MNP_LF_UNEXPECTED                   -7// в потоке данных встретился перевод строки
#define ERR_MNP_CR_UNEXPECTED                   -8// в потоке данных встретился возврат каретки
#define ERR_MNP_UNEXPECTED_CRC_CHAR             -9// в поле CRC встретился некоректный символ
#define ERR_MNP_CR_EXPECTED                     -10// должен был придти перевод каретки
#define ERR_MNP_LF_EXPECTED                     -11 // должен был придти перевод строки
#define ERR_MNP_CRC_ERROR                       -12// CRC не сошелся


#define PPER_command    "$PPER,0*" // команда самоконтроя МНП5

char MNP_get_message(void); // принимает сообщение
void MNP_message_reset (void); // срасывает принимающий автомат

char MNP_send_message(char* str); // отправляет сообщение

