#include "worldmodel.ih"

bool WorldModel::onMyFeet()
{
  //_debugLevel4(d_fieldNormal << " " << d_gyro << " " << d_footForces[0] << " " << d_footForces[1]);
//  return d_fieldNormal.getZ() > 0.98 && d_gyro.length() < 1.0 && d_footForces[0].getZ() > 0 && d_footForces[1].getZ() > 0;
    bool onmyleftleg = d_footForces[0].length() != 0; // 左足が地についてる
    bool onmyrightleg = d_footForces[1].length() != 0;// 右足が（ry
    if(onmyleftleg || onmyrightleg)
	d_onFeetCount = 0;
    else
	d_onFeetCount++;
    
    if(onmyleftleg)
	d_onLeftLeg = 0;
    else 
	d_onLeftLeg++;

    if(onmyrightleg)
	d_onRightLeg = 0;
    else
	d_onRightLeg++;
    
    return d_onFeetCount < 5 && d_onLeftLeg < 250 && d_onRightLeg < 250;

}

