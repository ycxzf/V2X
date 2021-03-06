#include "Sender.h"

using namespace std;

Sender::Sender()
{
}

Sender::Sender(list<CommunicationNode> &lc, Protocol &p)
{//初始化操作 注意指针引用
	oneCluster = &lc;
	protocol = &p;
}

Sender::~Sender()
{
	//delete oneCluster;
	//delete protocol;
}

void Sender::send() {//控制流程
	list<CommunicationNode>::iterator iter;//iter为容器的迭代器

	for (iter = (*oneCluster).begin(); iter != (*oneCluster).end(); iter++) {//遍历list中所有通信节点对象
		if ((*iter).getHaveMessage()) {//有消息要发
			list<Message> *info = NULL;
			info = (*iter).getMessageToSend();//获得要发的消息

			if ((*info).empty()) {//判断获取到的消息是否为空
				cout << "sender get " << (*iter).getNodeID() <<"message failed" << endl;
			}
			else cout << "sender get " << (*iter).getNodeID() << " message success" << endl;

			list<SliceMessage> * lsm = NULL;
			lsm = sendToProtocol((*protocol), (*info));//发送到协议栈处理

			//cout << "length of the sendQuene: " << (*lsm).size() << endl;
			//cout << "length of the sendQuene: " << (*lsm).back().getSize() << endl;

			SendQueue *sq = (*iter).getSendQueue();
			//cout << "sendQID: " << (*sq).getNodeID() << endl;

			if (sq != NULL) {
				sendToSQueue((*sq), (*lsm));//发送到发送队列
			}
			else cout << "sendQueue is NULL" << endl;
			delete lsm;

			(*iter).setHaveMessage(false);
		}
	}

	if ((*oneCluster).size() == 0) {
		cout << "this cluster has no member" << endl;
	}
}

list<SliceMessage>* Sender::sendToProtocol(Protocol &p, list<Message> &lm)//发送给协议栈处理
{
	list<SliceMessage>* lsm = NULL;
	lsm = p.cutMessage(lm);//发送给协议栈进行消息分片处理
	if ((*lsm).empty()) {//判断获取到的分片消息是否为空
		cout << "get from protocol message failed" << endl;
	}
	else cout << "get from protocol message success" << endl;
	return lsm;
}

void Sender::sendToSQueue(SendQueue &sq, list<SliceMessage> &lsm) {//发送给发送队列
	list<SliceMessage>::iterator iter;

	for (iter = lsm.begin(); iter != lsm.end(); iter++) {//遍历所有的分片消息
		sq.addMessage(*iter);
	}
	
}