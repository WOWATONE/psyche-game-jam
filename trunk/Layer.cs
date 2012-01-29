using UnityEngine;
using System.Collections;

public class Layer : MonoBehaviour {
	
	public int currentPosition;// 0 = back, 1 = front.
	public int layer_number;
	public float depth = 17;
	
	public bool pause = false;
	public string currentLevel;
	
	private Rect bxBack;
	private Rect bxTitle;
	private Rect bxResume;
	private Rect bxRetry;
	private Rect bxQuit;
	public GUIStyle titleStyle;
	public GUIStyle buttonStyle;

	// Use this for initialization
	void Start () {
		
		//currentPosition = 1;
		bxBack = new Rect(200, 140, 400, 300);
		bxTitle = new Rect(200, 140, 400, 35);
		bxResume = new Rect(bxBack.x+80, bxTitle.y+60, 250, 35);
		bxRetry = new Rect(bxBack.x+80, bxResume.y+40, 250, 35);
		bxQuit = new Rect(bxBack.x+80, bxRetry.y+40, 250, 35);
	}
	
	// Update is called once per frame
	void Update () 
	{
		if(Input.GetKey(KeyCode.Escape))
			pause = !pause;
	}
	
	void OnGUI()
	{
		if(pause == true)
		{
			// Make a background box
			GUI.Box(bxBack, "");
			GUI.Box(bxTitle, "PAUSED", titleStyle);
	
			// Make the first button. If it is pressed, Application.Loadlevel (1) will be executed
			if (GUI.Button(bxResume, "RESUME", buttonStyle)) 
			{
				pause = false;
			}
			
			if (GUI.Button(bxRetry, "RETRY", buttonStyle)) 
			{
				Application.LoadLevel(currentLevel);
			}
			
			if (GUI.Button(bxQuit, "QUIT", buttonStyle)) 
			{
				Application.LoadLevel("Menu");
			}
		}
	}
	
	public void ToFront(int target_layer){
		
		if (target_layer==layer_number)
		{
			if (currentPosition==0)
			{
				gameObject.transform.Translate(0,0,-depth);
				currentPosition=1;
			}
		}
		
	}
	
	public void ToBack(int target_layer){
	if (target_layer==layer_number)
		{	
			if (currentPosition==1)
			{
				gameObject.transform.Translate(0,0,depth);
				currentPosition=0;
			}
		}
		
	}
}
