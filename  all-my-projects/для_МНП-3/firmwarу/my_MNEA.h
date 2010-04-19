#ifndef _MY_MNEA_H
#define	_MY_MNEA_H

#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* _MY_MNEA_H */

#define MNP_WAIT_START                  0
#define MNP_WAIT_CRC_H                  1
#define MNP_WAIT_CRC_L                  2
#define MNP_WAIT_END                    3

// ������ ������ ��� ���������
#define	 MNP_MESSAGE_BUFFER_SIZE        128

//���� ������
#define ERR_RX_OVERFLOW                         -1 //������������ ��������� ������
#define ERR_MNP_MESSAGE_OVERFLOW                -2 //������������ ������ ���������
#define ERR_MNP_START_UNEXPECTED                -3 // ����������� ������ ������ ���������
#define ERR_MNP_END_UNEXPECTED                  -4 // ����������� ����� ���������.
#define ERR_MNP_CRC_NOT_CORRECT                 -5//CRC ������ �����������
#define ERR_MNP_CRC_ERROR                       -6// CRC �� �������

char MNP_get_message(void);
void MNP_message_reset (void);
unsigned char CRC_convert(unsigned char H,unsigned char L);
