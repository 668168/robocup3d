/* Copyright 2009 Hochschule Offenburg
 * Klaus Dorer, Mathias Ehret, Stefan Glaser, Thomas Huber,
 * Simon Raffeiner, Srinivasa Ragavan, Thomas Rinklin,
 * Joachim Schilling, Ingo Schindler, Rajit Shahi
 *
 * This file is part of magmaOffenburg.
 *
 * magmaOffenburg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * magmaOffenburg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with magmaOffenburg. If not, see <http://www.gnu.org/licenses/>.
 */
package magma.agent.worldmodel.localizer.impl;

import java.util.HashMap;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.worldmodel.localizer.ILocalizationFlag;
import magma.agent.worldmodel.localizer.ILocalizer;

import org.apache.commons.math.geometry.Vector3D;
import org.junit.Before;

import static org.easymock.EasyMock.createMock;
import static org.easymock.EasyMock.expect;

public abstract class LocalizerBaseTest
{
	ILocalizer testee;

	ILocalizationFlag G1L;

	ILocalizationFlag G2L;

	ILocalizationFlag G1R;

	ILocalizationFlag G2R;

	ILocalizationFlag F1L;

	ILocalizationFlag F2L;

	ILocalizationFlag F1R;

	ILocalizationFlag F2R;

	HashMap<String, ILocalizationFlag> flags = null;

	@Before
	public void setUp()
	{
		G1L = createMock(ILocalizationFlag.class);
		expect(G1L.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[0][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[0][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[0][2]));

		G2L = createMock(ILocalizationFlag.class);
		expect(G2L.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[1][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[1][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[1][2]));

		G1R = createMock(ILocalizationFlag.class);
		expect(G1R.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[2][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[2][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[2][2]));

		G2R = createMock(ILocalizationFlag.class);
		expect(G2R.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[3][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[3][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[3][2]));

		F1L = createMock(ILocalizationFlag.class);
		expect(F1L.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[4][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[4][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[4][2]));

		F2L = createMock(ILocalizationFlag.class);
		expect(F2L.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[5][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[5][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[5][2]));

		F1R = createMock(ILocalizationFlag.class);
		expect(F1R.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[6][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[6][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[6][2]));

		F2R = createMock(ILocalizationFlag.class);
		expect(F2R.getKnownPosition()).andStubReturn(
				new Vector3D(IServerConfigFilesConstants.LANDMARK_POSITIONS[7][0],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[7][1],
						IServerConfigFilesConstants.LANDMARK_POSITIONS[7][2]));

		flags = new HashMap<String, ILocalizationFlag>();
	}
}
