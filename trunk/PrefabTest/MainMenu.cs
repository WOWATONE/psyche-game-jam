using UnityEngine;
using System.Collections;

public class MainMenu : MonoBehaviour 
{
	//Variables
	private Rect bxBack;
	private Rect bxPlayButton;
	private Rect bxCreditsButton;
	private Rect bxExitButton;
	public string LoadLevel;
	public GUIStyle titleStyle;
	public GUIStyle buttonStyle;
	
	
	// Use this for initialization
	void Start ()
	{
		bxBack = new Rect(200, 150, 400, 500);
		bxPlayButton = new Rect(bxBack.x+120, bxBack.y+100, 150, 35);
		bxCreditsButton = new Rect(bxBack.x+120, bxPlayButton.y+40, 150, 35);
		bxExitButton = new Rect(bxBack.x+120, bxCreditsButton.y+40, 150, 35);
	}
	
	//Function OnGUI is called once per frame
	void OnGUI () 
	{
		// Make a background box
		//GUI.Box(bxBack, "Psyche", titleStyle);

		// Make the first button. If it is pressed, Application.Loadlevel (1) will be executed
		if (GUI.Button(bxPlayButton, "PLAY", buttonStyle)) 
		{
			Application.LoadLevel(LoadLevel);
		}
		
		if (GUI.Button(bxCreditsButton, "CREDITS", buttonStyle)) 
		{
			
		}
		
		if (GUI.Button(bxExitButton, "EXIT", buttonStyle)) 
		{
			Application.Quit();
		}
	}
}
