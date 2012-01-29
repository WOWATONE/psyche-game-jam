using UnityEngine;
using System.Collections;

using UnityEngine;
using System.Collections;

public class FinalAnimation : MonoBehaviour {
	
	public Texture[] CutSceneImages;
	public int framesPerSecond = 10;
	private int index = -1;
	private bool end = false;

	void Update() 
	{
		if(Input.GetKeyDown("space"))
		{
			if(index >= CutSceneImages.Length)
				end = true;
			else
			{
				index++;
			}
			
			if(!end)
			{
				renderer.material.mainTexture =  CutSceneImages[index];
			}
			else
				Application.LoadLevel("MainMenu");
		}
		
	}


}

