#ifndef COMMON_FUNCTION_HH
#define COMMON_FUNCTION_HH

#include "worldmodel.hh"
#include "math.hh"
#include "types.hh"

using namespace bats;

/* get player object between myself and pos.
 * e.g. in the following,
 * return Object in square ABCD
 * argments: pos = target position
 *           accuracy = the distance in square A, B, C and D
 *
 * if there is no object in the square, return NOBJECTS.
 * if there are two or more objects in the square,
 *  return the nearest Object.

 * * * * * * * * * * * * * * * * * *
 *                                 *
 *    A-----------------------B    *
 *    |                       |    *
 *  myself                   pos   *
 *    |                       |    *
 *    D-----------------------C    *
 *                                 *
 * * * * * * * * * * * * * * * * * *

 */
Types::Object getObjectBetweenPos(Vector3D pos, double accuracy);

// getObjectBetweenPosと同様の四角の中にObject objがあるかどうかを返す
bool objectExistBetweenPos(Vector3D pos, double accuracy, Types::Object obj);
bool existBetweenPos(Vector3D pos, double accuracy, Vector3D vec);

/* check the ball is kickable by right/left foot.
 * arguments:
 * toeWidth = the width of foot ( default 0.08 )
 * reack    = max distance between toe and ball ( default 0.08 )
 */
bool ballKickableByRight( double toeWidth=0.08, double reach=0.12 );
bool ballKickableByLeft( double toeWidth=0.08, double reach=0.12 );

/* calculate angle with Vector(1, 0, 0) (forward)
 * arguments:
 * vec        = original vector
 * setZtoZero = whether vec.setZ(0) or not (default true)
 * return: degree
 */
double getAngleWithStraight( Vector3D vec, bool setZtoZero=true );

/* if the ball is near flag1them or flag2them, return true.
 * corner = Triangle ( goal1(2)them, flag1(2)them, point( on sideline ))
 * point  = on sideline and 2.0 distance from goalline

 * * * * * *
 * example *
 * * * * * * * * * * *
 *                   *
 *              |    *
 *             goal  *
 *             /|    *
 *            / |    *
 *           /  |    *
 *          /   |    *
 *         /    |    *
 *        /     |    *
 *  ----point--flag  *
 *                   *
 *       |  2.0 |    *
 *                   *
 * * * * * * * * * * *

 */
bool isBallNearCorner();

#endif // COMMON_FUNCTION_HH
