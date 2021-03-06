#pragma once
#ifndef COMMUNICATIONNODE_H
#define COMMUNICATIONNODE_H

#include "Message.h"
#include "SendQueue.h"
#include "ReceiveQueue.h"
#include <iostream>
#include <list>
#include <limits>

/*******************************
 *通信节点类
********************************/
class CommunicationNode
{
public:
	//构造函数
	CommunicationNode();
	CommunicationNode(long id, float lgt, float lat, float sp,
		float tp, float rp, float tr, std::list<Message> &sm, std::list<Message> & rm, SendQueue &sq, ReceiveQueue &rq);
	//析构函数
	~CommunicationNode();

	//获取节点ID
	long getNodeID();
	//获取经度信息
	float getLongitude();
	//获取纬度信息
	float getLatitude();
	//获取速度信息
	float getSpeed();
	//获取发射功率信息
	float getTPower();
	//获取接收功率信息
	float getRPower();
	//获取发射速率信息
	float getTRate();
	//获取要发送的消息
	list<Message>* getMessageToSend();
	//获取要接收的消息
	list<Message>* getMessageToRecv();
	//获取发送队列
	SendQueue* getSendQueue();
	//获取接收队列
	ReceiveQueue* getReceiveQueue();
	//获取分簇情况
	int getCrowd();
	//是否有消息要发送
	bool getHaveMessage();

	//设置节点ID
	void setNodeID(int id);
	//设置经度信息
	void setLongitude(float lon);
	//设置纬度信息
	void setlatitude(float lat);
	//设置速度信息
	void setSpeed(float sp);
	//设置发射功率信息
	void setTPower(float tPow);
	//设置接收功率信息
	void setRPower(float rPow);
	//设置发射速率信息
	void setTRate(float trate);
	//设定发送消息
	void setSendMessage(list<Message> &sm);
	//设定接收消息
	void setRecvMessage(list<Message> &rm);
	//设置分簇情况
	void setCrowd(int c);
	//设置消息发送情况
	void setHaveMessage(bool msg);
	//判断当前节点是否有消息接收并且接收消息中是否有已经传输完成的
	bool isFinished();

	std::string toJson();
	
	

private:
	long nodeID = (numeric_limits<long>::min)();       //节点ID
	float longitude;   //经度
	float latitude;    //纬度
	float speed;       //速度
	float tPower;      //发射功率
	float rPower;      //接收功率
	float tRate;       //发射速率
	int crowd = 0;     //分簇相关信息，0表示当前通信节点未进行分簇，1表示当前节点进行了分簇
	bool haveMessage = false; //是否有消息要发
	std::list<Message> *send_msg;  //要发送的消息
	std::list<Message> *recv_msg; //接收到的消息
	SendQueue *sendQ;  //发送队列
	ReceiveQueue *receiveQ; //接收队列

};

#endif