#include "worldmodel.ih"

//coordinates of the torso frame referentiel in the field coordinates
void WorldModel::updateNaoFRef() {
	//std::cout << "wm.updateNaoRef" << std::endl;
	if (d_first && isCheck) {

		std::cout << "inside" << std::endl;

		//initialization of velocity vector
		d_velocity = Vector3D(0, 0, 0);

		//calculation of the transformation matrix with flag vision
		flagNaoToField();

		d_first = false;
	}

	//calculation of the robots coordinates at t = 0
	//not good, moreover some robots begins to move during the before kickoff
	else if ((d_playMode == BEFORE_KICKOFF || d_playMode == GOAL_THEM
			|| d_playMode == GOAL_US || d_playMode == GOAL_RIGHT || d_playMode
			== GOAL_LEFT || d_time == 0) ) { //&& d_worldCoordAvailable


		//calculation of the transformation matrix with flag vision
		flagNaoToField();

	}

	//calculation of the robots coordinates at t != 0
	else {
		//if at least one landmark is visible
		if (visibleLandmarkNum() > 1) {

			double delta1;
			double delta2;

			//to improve, doesn't work for now
			if (visibleObject(Types::FLAG1L) || visibleObject(Types::FLAG2L)
					|| visibleObject(Types::GOAL1L) || visibleObject(
					Types::GOAL1L)) {

				const Vector3F distToFlagR1(
						d_objectPositionsW[Types::FLAG1L].getMu());

				const Vector3F distToFlagR2(
						d_objectPositionsW[Types::FLAG2L].getMu());

				Vector3F distToFlagF1 = d_transform * distToFlagR1;
				Vector3F distToFlagF2 = d_transform * distToFlagR2;

				delta1 = distToFlagF1.length() - distToFlagR1.length();
				delta2 = distToFlagF2.length() - distToFlagR2.length();

			} else {

				const Vector3F distToFlagR1(
						d_objectPositionsW[Types::FLAG1R].getMu());

				const Vector3F distToFlagR2(
						d_objectPositionsW[Types::FLAG2R].getMu());

				Vector3F distToFlagF1 = d_transform * distToFlagR1;
				Vector3F distToFlagF2 = d_transform * distToFlagR2;

				delta1 = distToFlagF1.length() - distToFlagR1.length();
				delta2 = distToFlagF2.length() - distToFlagR2.length();
			}

			//if the difference betwwen the distances are superior to 5%
			//and world coordinates are available
			if ((fabs(delta1) > 0.1 || fabs(delta2) > 0.1)
					&& d_worldCoordAvailable) {

				//then reclaculation of the transformation matrix with flags.
				flagNaoToField();

				d_lastCoordUpdate = d_gameTime;

				return;
			}
		}

		double delta_t = d_timeStep;
		if (delta_t == 0) {
			delta_t = 0.02; // the length of one step
		}

		double delta = d_gameTime - d_lastCoordUpdate;

		//calculation of the translation vector
		Vector3D v_trans = d_acceleration * (0.5 * delta * delta) + d_velocity
				* delta;
		//calculation of the new velocity vector
		d_velocity = d_velocity + d_acceleration * (delta);

		//calculation of the rotation matrix
		Matrix4D rot = Matrix4D::rotation(Vector3D(d_gyro.getX() * delta_t
				* M_PI / 180.0, d_gyro.getY() * delta_t * M_PI / 180.0,
				d_gyro.getZ() * delta_t * M_PI / 180.0));

		//calculation of transformation matrix P = TR
		rot.set(3, 0, v_trans.getX());
		rot.set(3, 1, v_trans.getY());
		rot.set(3, 2, v_trans.getZ());

		//calculation of the new robot frame referentiel in the field coordinates
		d_transform = rot * d_transform;

	}

	d_lastCoordUpdate = d_gameTime;
}

//calculation of the transformation matrix with flag vision
void WorldModel::flagNaoToField() {

	//TODO Do I need to normalize ???

	//Matrix of flags in robots referentiel R
	Matrix4D R;

	//Matrix of flags in fiels referentiel F
	Matrix4D F;

	if (d_team == RIGHT && (visibleObject(Types::FLAG1THEM) || visibleObject(
			Types::FLAG2THEM) || visibleObject(Types::GOAL1THEM)
			|| visibleObject(Types::GOAL2THEM))) {

		R.set(0, 0, (d_objectPositionsW[Types::FLAG1THEM].getMu()).getX());
		R.set(1, 0, (d_objectPositionsW[Types::FLAG1THEM].getMu()).getY());
		R.set(2, 0, (d_objectPositionsW[Types::FLAG1THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 0, 1);
		R.set(0, 1, (d_objectPositionsW[Types::FLAG2THEM].getMu()).getX());
		R.set(1, 1, (d_objectPositionsW[Types::FLAG2THEM].getMu()).getY());
		R.set(2, 1, (d_objectPositionsW[Types::FLAG2THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 1, 1);
		R.set(0, 2, (d_objectPositionsW[Types::GOAL1THEM].getMu()).getX());
		R.set(1, 2, (d_objectPositionsW[Types::GOAL1THEM].getMu()).getY());
		R.set(2, 2, (d_objectPositionsW[Types::GOAL1THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 2, 1);
		R.set(0, 3, (d_objectPositionsW[Types::GOAL2THEM].getMu()).getX());
		R.set(1, 3, (d_objectPositionsW[Types::GOAL2THEM].getMu()).getY());
		R.set(2, 3, (d_objectPositionsW[Types::GOAL2THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 3, 1);

		F.set(0, 0, s_globalFlagCoordMap[Types::FLAG1L].getX());
		F.set(1, 0, s_globalFlagCoordMap[Types::FLAG1L].getY());
		F.set(2, 0, s_globalFlagCoordMap[Types::FLAG1L].getZ());
		F.set(3, 0, 1);
		F.set(0, 1, s_globalFlagCoordMap[Types::FLAG2L].getX());
		F.set(1, 1, s_globalFlagCoordMap[Types::FLAG2L].getY());
		F.set(2, 1, s_globalFlagCoordMap[Types::FLAG2L].getZ());
		F.set(3, 1, 1);
		F.set(0, 2, s_globalFlagCoordMap[Types::GOAL1L].getX());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1L].getY());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1L].getZ());
		F.set(3, 2, 1);
		F.set(0, 3, s_globalFlagCoordMap[Types::GOAL2L].getX());
		F.set(1, 3, s_globalFlagCoordMap[Types::GOAL2L].getY());
		F.set(2, 3, s_globalFlagCoordMap[Types::GOAL2L].getZ());
		F.set(3, 3, 1);

	} else if (d_team == LEFT && (visibleObject(Types::FLAG1THEM)
			|| visibleObject(Types::FLAG2THEM) || visibleObject(
			Types::GOAL1THEM) || visibleObject(Types::GOAL2THEM))) {

		R.set(0, 0, (d_objectPositionsW[Types::FLAG1THEM].getMu()).getX());
		R.set(1, 0, (d_objectPositionsW[Types::FLAG1THEM].getMu()).getY());
		R.set(2, 0, (d_objectPositionsW[Types::FLAG1THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 0, 1);
		R.set(0, 1, (d_objectPositionsW[Types::FLAG2THEM].getMu()).getX());
		R.set(1, 1, (d_objectPositionsW[Types::FLAG2THEM].getMu()).getY());
		R.set(2, 1, (d_objectPositionsW[Types::FLAG2THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 1, 1);
		R.set(0, 2, (d_objectPositionsW[Types::GOAL1THEM].getMu()).getX());
		R.set(1, 2, (d_objectPositionsW[Types::GOAL1THEM].getMu()).getY());
		R.set(2, 2, (d_objectPositionsW[Types::GOAL1THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 2, 1);
		R.set(0, 3, (d_objectPositionsW[Types::GOAL2THEM].getMu()).getX());
		R.set(1, 3, (d_objectPositionsW[Types::GOAL2THEM].getMu()).getY());
		R.set(2, 3, (d_objectPositionsW[Types::GOAL2THEM].getMu()).getZ()
				- 0.17);
		R.set(3, 3, 1);

		F.set(0, 0, s_globalFlagCoordMap[Types::FLAG1R].getX());
		F.set(1, 0, s_globalFlagCoordMap[Types::FLAG1R].getY());
		F.set(2, 0, s_globalFlagCoordMap[Types::FLAG1R].getZ());
		F.set(3, 0, 1);
		F.set(0, 1, s_globalFlagCoordMap[Types::FLAG2R].getX());
		F.set(1, 1, s_globalFlagCoordMap[Types::FLAG2R].getY());
		F.set(2, 1, s_globalFlagCoordMap[Types::FLAG2R].getZ());
		F.set(3, 1, 1);
		F.set(0, 2, s_globalFlagCoordMap[Types::GOAL1R].getX());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1R].getY());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1R].getZ());
		F.set(3, 2, 1);
		F.set(0, 3, s_globalFlagCoordMap[Types::GOAL2R].getX());
		F.set(1, 3, s_globalFlagCoordMap[Types::GOAL2R].getY());
		F.set(2, 3, s_globalFlagCoordMap[Types::GOAL2R].getZ());
		F.set(3, 3, 1);

	} else if (d_team == LEFT && (visibleObject(Types::FLAG1US)
			|| visibleObject(Types::FLAG2US) || visibleObject(Types::GOAL1US)
			|| visibleObject(Types::GOAL2US))) {

		R.set(0, 0, (d_objectPositionsW[Types::FLAG1US].getMu()).getX());
		R.set(1, 0, (d_objectPositionsW[Types::FLAG1US].getMu()).getY());
		R.set(2, 0, (d_objectPositionsW[Types::FLAG1US].getMu()).getZ() - 0.17);
		R.set(3, 0, 1);
		R.set(0, 1, d_objectPositionsW[Types::FLAG2US].getMu().getX());
		R.set(1, 1, d_objectPositionsW[Types::FLAG2US].getMu().getY());
		R.set(2, 1, d_objectPositionsW[Types::FLAG2US].getMu().getZ() - 0.17);
		R.set(3, 1, 1);
		R.set(0, 2, d_objectPositionsW[Types::GOAL1US].getMu().getX());
		R.set(1, 2, d_objectPositionsW[Types::GOAL1US].getMu().getY());
		R.set(2, 2, d_objectPositionsW[Types::GOAL1US].getMu().getZ() - 0.17);
		R.set(3, 2, 1);
		R.set(0, 3, d_objectPositionsW[Types::GOAL2US].getMu().getX());
		R.set(1, 3, d_objectPositionsW[Types::GOAL2US].getMu().getY());
		R.set(2, 3, d_objectPositionsW[Types::GOAL2US].getMu().getZ() - 0.17);
		R.set(3, 3, 1);

		F.set(0, 0, s_globalFlagCoordMap[Types::FLAG1L].getX());
		F.set(1, 0, s_globalFlagCoordMap[Types::FLAG1L].getY());
		F.set(2, 0, s_globalFlagCoordMap[Types::FLAG1L].getZ());
		F.set(3, 0, 1);
		F.set(0, 1, s_globalFlagCoordMap[Types::FLAG2L].getX());
		F.set(1, 1, s_globalFlagCoordMap[Types::FLAG2L].getY());
		F.set(2, 1, s_globalFlagCoordMap[Types::FLAG2L].getZ());
		F.set(3, 1, 1);
		F.set(0, 2, s_globalFlagCoordMap[Types::GOAL1L].getX());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1L].getY());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1L].getZ());
		F.set(3, 2, 1);
		F.set(0, 3, s_globalFlagCoordMap[Types::GOAL2L].getX());
		F.set(1, 3, s_globalFlagCoordMap[Types::GOAL2L].getY());
		F.set(2, 3, s_globalFlagCoordMap[Types::GOAL2L].getZ());
		F.set(3, 3, 1);

	} else if (d_team == RIGHT && (visibleObject(Types::FLAG1US)
			|| visibleObject(Types::FLAG2US) || visibleObject(Types::GOAL1US)
			|| visibleObject(Types::GOAL2US))) {

		R.set(0, 0, (d_objectPositionsW[Types::FLAG1US].getMu()).getX());
		R.set(1, 0, (d_objectPositionsW[Types::FLAG1US].getMu()).getY());
		R.set(2, 0, (d_objectPositionsW[Types::FLAG1US].getMu()).getZ() - 0.17);
		R.set(3, 0, 1);
		R.set(0, 1, d_objectPositionsW[Types::FLAG2US].getMu().getX());
		R.set(1, 1, d_objectPositionsW[Types::FLAG2US].getMu().getY());
		R.set(2, 1, d_objectPositionsW[Types::FLAG2US].getMu().getZ() - 0.17);
		R.set(3, 1, 1);
		R.set(0, 2, d_objectPositionsW[Types::GOAL1US].getMu().getX());
		R.set(1, 2, d_objectPositionsW[Types::GOAL1US].getMu().getY());
		R.set(2, 2, d_objectPositionsW[Types::GOAL1US].getMu().getZ() - 0.17);
		R.set(3, 2, 1);
		R.set(0, 3, d_objectPositionsW[Types::GOAL2US].getMu().getX());
		R.set(1, 3, d_objectPositionsW[Types::GOAL2US].getMu().getY());
		R.set(2, 3, d_objectPositionsW[Types::GOAL2US].getMu().getZ() - 0.17);
		R.set(3, 3, 1);

		F.set(0, 0, s_globalFlagCoordMap[Types::FLAG1R].getX());
		F.set(1, 0, s_globalFlagCoordMap[Types::FLAG1R].getY());
		F.set(2, 0, s_globalFlagCoordMap[Types::FLAG1R].getZ());
		F.set(3, 0, 1);
		F.set(0, 1, s_globalFlagCoordMap[Types::FLAG2R].getX());
		F.set(1, 1, s_globalFlagCoordMap[Types::FLAG2R].getY());
		F.set(2, 1, s_globalFlagCoordMap[Types::FLAG2R].getZ());
		F.set(3, 1, 1);
		F.set(0, 2, s_globalFlagCoordMap[Types::GOAL1R].getX());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1R].getY());
		F.set(2, 2, s_globalFlagCoordMap[Types::GOAL1R].getZ());
		F.set(3, 2, 1);
		F.set(0, 3, s_globalFlagCoordMap[Types::GOAL2R].getX());
		F.set(1, 3, s_globalFlagCoordMap[Types::GOAL2R].getY());
		F.set(2, 3, s_globalFlagCoordMap[Types::GOAL2R].getZ());
		F.set(3, 3, 1);
	}

	/*std::cout << "nb de flags depuis le robot" << endl;
	std::cout << visibleLandmarkNum() << endl << std::endl;

	std::cout << "matrice des flags depuis le robot" << endl;
	std::cout << R << endl << std::endl << std::endl;*/

	//Vector3D goalPos = getObjectPosition(Types::GOAL1THEM).getMu();

/*	std::cout << "ballPos : ";
	std::cout << goalPos.getX() << " ";
	std::cout << goalPos.getY() << " ";
	std::cout << goalPos.getZ() << " ";
	std::cout << ";" << std::endl;
*/
	//inverse matrix of R = R'
	Matrix4D IR = R.inverse2();

	/*std::cout << "matrice inverse" << endl;
	std::cout << IR << endl << std::endl<< std::endl;*/

	//transfomation matrix T = F*R'
	d_transform = F * IR;


	/*std::cout << "matrice de transfo" << endl;
	std::cout << d_transform << endl << std::endl;*/
}
