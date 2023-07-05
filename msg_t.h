//
// Created by vitto on 03/07/2023.
//

#ifndef HOMEWORK_1_MSG_T_H
#define HOMEWORK_1_MSG_T_H
class msg_t{
public:
    msg_t();
    msg_t(void* content_);
    void *msg_init(void *content_);
    void msg_destroy(msg_t *msg);
    msg_t* msg_copy(const msg_t* msg);
private:
    void *content;
public:
    void *getContent() const;
    void setContent(void *content);
};
#endif //HOMEWORK_1_MSG_T_H
