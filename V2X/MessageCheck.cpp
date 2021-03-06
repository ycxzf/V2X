
#include <math.h>
#include "MessageCheck.h"
#include "CommunicationNode.h"
#include "Util.h"
#include "constUtil.h"

bool errorCheck(SliceMessage sMsg)
{
	return sMsg.getError();
}

//可达检测
bool reachCheck(SliceMessage sMsg, CommunicationNode dest, list<CommunicationNode> communicationNodes)
{
	CommunicationNode sourceNode = getNode(communicationNodes, sMsg.getSourceAddress());
	/*
	double x1 = sourceNode.getLongitude();
	double y1 = sourceNode.getLatitude();
	double x2 = dest.getLongitude();
	double y2 = dest.getLatitude();
	double radLat1 = y1*PI / 180;
	double radLat2 = y2*PI / 180;
	double radLon1 = x1*PI / 180;
	double radLon2 = y2*PI / 180;
	double a = radLat1 - radLat2;
	double b = radLon1 - radLon2;
	double s = 2 * asin(sqrt(pow(sin(a / 2), 2) + cos(radLat1)*cos(radLat2)*pow(sin(b / 2), 2)));
	s = s*EARTH_RADIUS;
*/

	double s = getDistance(sourceNode, dest);
	if (s <= REACHDISTANCE)
	{
		return true;
	}
	else {
		return false;
	}
}