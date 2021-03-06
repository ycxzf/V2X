#include "Receiver.h"
using namespace std;

Receiver::Receiver()
{
}

Receiver::Receiver(list<CommunicationNode> &lc, Protocol &p)
{
	objectManager = &lc;
	protocol = &p;
}

Receiver::~Receiver() {}

void Receiver::receive()//控制流程
{
	list<CommunicationNode>::iterator iter;//iter为容器的迭代器

	for (iter = (*objectManager).begin(); iter != (*objectManager).end(); iter++) {//遍历list中所有通信节点对象
		ReceiveQueue *rq = (*iter).getReceiveQueue();
		if ((*rq).isEmpty() != true) {//有消息要收			
			list<SliceMessage> *sliceInfo = NULL;
			sliceInfo = getFromRQuene((*rq));//获取消息

			if (sliceInfo != NULL) {
				//cout << "receiver get SliceMessage: " << sliceInfo->back().getSourceAddress() << " "
				//	<< sliceInfo->back().getDestinationAddress() << endl;
				cout << "SliceMessage size: " << sliceInfo->size() << endl;
			}
			
			list<Message> *info = NULL;
			info = sendToProtocol((*protocol), (*sliceInfo));//发送到协议栈处理
			//cout << "delay: " << (*info).back().getDelay() << endl;
			cout << "Info size: " << (*info).size() << endl;
			//cout << "Info message size: " << (*info).back().getSize() << endl;

			(*iter).setRecvMessage((*info));//将消息发送给对应的节点

			delete sliceInfo, info;
		}
	}
}

list<SliceMessage> * Receiver::getFromRQuene(ReceiveQueue &rq)//从接收队列获取分片消息
{
	list<SliceMessage> * sMsgs = new list<SliceMessage>;
	queue<SliceMessage> * tmp = (rq).getSliceMessage();
	while ((*tmp).empty() != true) {
		(*sMsgs).push_back((*tmp).front());
		(*tmp).pop();
	}
	//调用当前通信节点的接收队列的getSliceMessage方法获取分片消息
	if ((*sMsgs).empty()) {//判断获取到的分片消息是否为空
		cout << "get slicemessage failed!" << endl;
	}
	else cout << "get slicemessage success" << endl;
	delete tmp;
	return sMsgs;
}

list<Message> * Receiver::sendToProtocol(Protocol &p, list<SliceMessage> &lsm)//发送给协议栈处理
{
	list<Message> * lm = NULL;
	lm = p.mergeMessage(lsm);//发送给协议栈进行消息整合处理
	if ((*lm).empty()) {//判断获取到的整合消息是否为空
		cout << "get message failed!" << endl;
	}
	else cout << "get message success" << endl;
	return lm;
}
