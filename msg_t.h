//
// Created by vitto on 03/07/2023.
//

#ifndef HOMEWORK_1_MSG_T_H
#define HOMEWORK_1_MSG_T_H
class msg_t{
public:
    msg_t();
    msg_t *msg_init(void *content_);
    void msg_destroy(msg_t *msg);
    void *content;
};
#endif //HOMEWORK_1_MSG_T_H
