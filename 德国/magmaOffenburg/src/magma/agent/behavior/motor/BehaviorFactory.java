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
package magma.agent.behavior.motor;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;
import javax.xml.transform.Source;
import javax.xml.transform.TransformerFactoryConfigurationError;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;
import javax.xml.validation.Validator;

import magma.agent.IServerConfigFilesConstants;
import magma.agent.agentmodel.IAgentModel;
import magma.agent.behavior.IBehavior;
import magma.agent.behavior.ICoordinator;
import magma.agent.behavior.basic.BehaviorParameter;
import magma.agent.behavior.basic.Step;
import magma.agent.behavior.perform.IHingePerform;
import magma.agent.behavior.perform.IUniversalPerform;
import magma.agent.behavior.perform.impl.LinearPerform;
import magma.agent.worldmodel.IGlobalMap;

import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 * @author Ingo Schindler, Stefan Glaser
 * 
 */
public class BehaviorFactory
{
	private static ICoordinator coordinator;

	private static IAgentModel agent;

	private static IGlobalMap world;

	private final static File root = new File("build/classes/xml");

	private static Validator validator;

	public static Map<String, IBehavior> createBehaviors(IGlobalMap worldModel,
			IAgentModel agentModel, ICoordinator c, BehaviorParameter params)
	{
		init();

		coordinator = c;
		agent = agentModel;
		world = worldModel;
		HashMap<String, IBehavior> behaviors = new HashMap<String, IBehavior>();

		// Set filter for *.xml Files
		FilenameFilter filter = new FileListFilter("", "xml");

		// get all *.xml-Files in Directory
		File[] behaviorsFiles = root.listFiles(filter);

		for (int i = 0; i < behaviorsFiles.length; i++) {
			// 4. Parse the document you want to check.

			if (validateXml(behaviorsFiles[i])) {
				IBehavior behave = parse(behaviorsFiles[i], params);
				behaviors.put(behave.getName(), behave);
			}

		}

		// saveBehavior(behaviors.get(0));

		return behaviors;
	}

	public static void saveBehavior(IBehavior behavior)
	{
		// TODO: generate a new File
		Document document;
		try {
			document = DocumentBuilderFactory.newInstance().newDocumentBuilder()
					.newDocument();

			Element ordersRootElement = document.createElement("behavior");

			document.appendChild(ordersRootElement);
			Element nameElement = document.createElement("name");
			Element stepsElement = document.createElement("steps");

			ordersRootElement.appendChild(nameElement);
			ordersRootElement.appendChild(stepsElement);

			String name = behavior.getName();
			nameElement.setNodeValue(name);

			// TODO: write to a file

			Map<Integer, Step> steps = ((MotorBehavior) behavior).getSteps();

			for (Integer stepId : steps.keySet()) {

				Step s = steps.get(stepId);

				Element stepElement = document.createElement("step");
				stepElement.setAttribute("id", stepId.toString());

				stepsElement.appendChild(stepElement);

				Map<String, IHingePerform> performs = s.getHingePerforms();
				Map<String, float[]> triggers = s.getTriggers();

				Element perform = document.createElement("perform");
				stepElement.appendChild(perform);

				for (String i : performs.keySet()) {
					LinearPerform p = (LinearPerform) performs.get(i);

					Element effector = document.createElement("effector");

					effector.setAttribute("name", i);

					Element target = document.createElement("target");
					Element speed = document.createElement("speed");

					effector.appendChild(target);
					effector.appendChild(speed);

					target.setTextContent("" + p.getTarget());
					speed.setTextContent("" + p.getSpeed());

					perform.appendChild(effector);

				}

				Element trigger = document.createElement("trigger");
				stepElement.appendChild(trigger);

				for (String i : triggers.keySet()) {
					float[] t = triggers.get(i);
					Element hinge = document.createElement("hinge");

					hinge.setAttribute("name", i);

					Element target = document.createElement("target");

					hinge.appendChild(target);

					target.setTextContent("" + t[0]);

					trigger.appendChild(hinge);

				}

			}

			//			
			// TransformerFactory.newInstance().newTransformer().transform(
			// new DOMSource(document),
			// new StreamResult("/home/stilnox/test.xml"));

		} catch (ParserConfigurationException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		} catch (TransformerFactoryConfigurationError e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	/**
	 * 
	 */
	private static void init()
	{
		// TODO Auto-generated method stub

		SchemaFactory factory = SchemaFactory
				.newInstance("http://www.w3.org/2001/XMLSchema");

		File schemaLocation = new File(root.getAbsolutePath() + "/"
				+ "behavior.xsd");
		Schema schema;
		try {
			schema = factory.newSchema(schemaLocation);
			validator = schema.newValidator();
		} catch (SAXException e) {
			System.out.println("Schema could not be loaded");
			e.printStackTrace();
		}
	}

	private static boolean validateXml(File xml)
	{

		try {
			Source source = new StreamSource(xml);
			validator.validate(source);
			System.out.println(xml + " is valid.");

			return true;

		} catch (SAXException ex) {
			System.out.println("Behavior is not valid: " + xml);
			System.out.println(ex.getMessage());
		} catch (IOException e) {
			System.out.println("File could not be found: " + xml);

		}
		return false;
	}

	private static IBehavior parse(File xml, BehaviorParameter params)
	{
		HashMap<Integer, Step> steps = new HashMap<Integer, Step>();
		HashMap<String, IHingePerform> hingePerforms = new HashMap<String, IHingePerform>();
		HashMap<String, IUniversalPerform> universalPerforms = null;
		HashMap<String, float[]> targets = new HashMap<String, float[]>();

		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		// factory.setNamespaceAware( true );
		// factory.setValidating( true );
		DocumentBuilder builder;
		try {

			builder = factory.newDocumentBuilder();
			Document document = builder.parse(xml);
			document.normalize();

			String name = document.getElementsByTagName("name").item(0)
					.getTextContent();

			System.out.println("BehaviorName: " + name);

			NodeList nl = document.getElementsByTagName("step");

			Step step = null;

			for (int i = 0; i < nl.getLength(); i++) {

				int stepId = Integer.parseInt(nl.item(i).getAttributes().item(0)
						.getNodeValue());
				// System.out.println("\tID: " + stepId);

				hingePerforms = new HashMap<String, IHingePerform>();
				targets = new HashMap<String, float[]>();
				int nextStepId = 0;

				for (int j = 0; j < nl.item(i).getChildNodes().getLength(); j++) {
					Node tmp = nl.item(i).getChildNodes().item(j);
					if (tmp.getNodeName().equals("next")) {
						if (!nl.item(i).getChildNodes().item(j).getTextContent()
								.equals("")) {
							nextStepId = Integer.parseInt(nl.item(i).getChildNodes()
									.item(j).getTextContent());
						}
						// System.out.println("\t\tNext Step: " + nextStepId);
					} else if (tmp.getNodeName().equals("perform")) {
						// System.out.println("\t\tPerforms");
						NodeList performers = nl.item(i).getChildNodes().item(j)
								.getChildNodes();

						for (int k = 0; k < performers.getLength(); k++) {
							if (performers.item(k).getNodeName().equals("effector")) {
								NodeList eff = performers.item(k).getChildNodes();
								float target = Float.parseFloat(eff.item(1)
										.getTextContent());
								float speed = Float.parseFloat(eff.item(3)
										.getTextContent());
								String joint = performers.item(k).getAttributes().item(
										0).getTextContent();
								// System.out.println("\t\t\tJoint: " + joint);
								// System.out.println("\t\t\t\tTarget: " + target);
								// System.out.println("\t\t\t\tSpeed: " + speed);

								// TODO: make a clean name-check
								int l = 0;
								while (l < IServerConfigFilesConstants.HINGEJOINT_NAMES.length) {
									if (IServerConfigFilesConstants.HINGEJOINT_NAMES[l]
											.equals(joint)) {
										if (params.getSpeedFactors() != null) {
											speed *= params.getSpeedFactors()[nextStepId];
										}
										hingePerforms
												.put(
														IServerConfigFilesConstants.HINGEJOINT_NAMES[l],
														new LinearPerform(
																IServerConfigFilesConstants.HINGEJOINT_NAMES[l],
																target, speed));
										l = IServerConfigFilesConstants.HINGEJOINT_NAMES.length;
									}
									l++;
								}

							}
						}

					} else if (tmp.getNodeName().equals("trigger")) {
						// System.out.println("\t\tTriggers");

						NodeList trigger = nl.item(i).getChildNodes().item(j)
								.getChildNodes();
						for (int k = 0; k < trigger.getLength(); k++) {
							if (trigger.item(k).getNodeName().equals("hinge")) {
								NodeList eff = trigger.item(k).getChildNodes();
								float target = Float.parseFloat(eff.item(1)
										.getTextContent());
								String joint = trigger.item(k).getAttributes().item(0)
										.getTextContent();
								// System.out.println("\t\t\tJoint: " + joint);
								// System.out.println("\t\t\t\tTarget: " + target);
								// System.out.println("\t\t\t\tSpeed: " + comperator);

								// TODO: make a clean name-check
								int l = 0;
								while (l < IServerConfigFilesConstants.HINGEJOINT_NAMES.length) {
									if (IServerConfigFilesConstants.HINGEJOINT_NAMES[l]
											.equals(joint)) {
										// System.out.println("\t\t\t\tTarget: " +
										// target);
										targets.put(joint, new float[] { target });
										l = IServerConfigFilesConstants.HINGEJOINT_NAMES.length;
									}
									l++;
								}
							}
						}
					}
				}
				// System.out.println("Next Step ID: " + nextStepId);
				step = new Step(nextStepId, hingePerforms, universalPerforms,
						targets);

				steps.put(stepId, step);
			}

			return new XMLMotorBehavior(name, world, agent, coordinator, steps);
		} catch (Exception e) {
			e.printStackTrace();
			return null;
		}
	}
}

class FileListFilter implements FilenameFilter
{
	private final String name;

	private final String extension;

	public FileListFilter(String name, String extension)
	{
		this.name = name;
		this.extension = extension;
	}

	public boolean accept(File directory, String filename)
	{
		boolean fileOK = true;

		if (name != null) {
			fileOK &= filename.startsWith(name);
		}

		if (extension != null) {
			fileOK &= filename.endsWith('.' + extension);
		}
		return fileOK;
	}
}