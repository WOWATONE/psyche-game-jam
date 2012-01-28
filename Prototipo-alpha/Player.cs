using UnityEngine;
using System.Collections;

public class Player : MonoBehaviour {
	
	public float WalkingSpeed = 5;				//Velocidade que o objeto anda
	public float JumpSpeed;						//Altura que o Player pula
	public float JumpHeight;
	public Layer layer;	
	private float WalkingDir;					//Direção em que o player está se movimentando (!= de onde está olhando)
	public float gravity=40f;
	private bool isJumping;
	private float JumpHeightAux;
	
	bool isOnAir;
	
	public int dt=0;
	
	public float vely = 0;
	
	// Use this for initialization
	void Start () {
		//gravity = 30F;
		isJumping = false;
		isOnAir = true;
	}
	
	// Update is called once per frame
	void Update () 
	{
		gameObject.transform.Translate(0,0,2-gameObject.transform.position.z);
		
		Movement();
	}
	
	void Movement()	
	{	
		CharacterController CharController = GetComponent<CharacterController>();
		Vector3 moveDirection = Vector3.zero;
		
		moveDirection = new Vector3(Input.GetAxis("Horizontal"), 0, 0);
		moveDirection = transform.TransformDirection(moveDirection);
		moveDirection *= WalkingSpeed;
		
		//CharController.Move(moveDirection * Time.deltaTime);
		
		//Pula caso o botão JUMP for pressionado e se ele já não estiver pulando
		if((Input.GetAxis("Jump") != 0) && CharController.isGrounded)
		{
			//JumpHeightAux = gameObject.transform.position.y + JumpHeight;
			//print(moveDirection.y);
			isJumping = true;
		}
		else
		{
			isJumping = false;	
		}
		/*if(isJumping)
		{	dt++;
			vely = JumpSpeed-dt*gravity;
			moveDirection.y += vely;
			//if(gameObject.transform.position.y > JumpHeightAux)
			//	isJumping = false;
		}
		else 
		{
			if (isOnAir)
			{
				dt++;
				vely = -dt*gravity;
				moveDirection.y += vely;
				
			}
			else
			{
				dt = 0;
			}
		}
		CharController.Move(moveDirection*Time.deltaTime);*/
		
		//CharacterController contr = getComponent<CharacterController>();
		Vector3 dir = new Vector3(Input.GetAxis("Horizontal"), 0, Input.GetAxis("Vertical"));
		
		dir.y = CharController.velocity.y - gravity * Time.deltaTime;
 
        //are we jumping?
        if (isJumping)
        {
            dir.y = JumpSpeed * gravity * Time.deltaTime;      
        }
 
 
        //move our character
        CharController.Move((dir+moveDirection) * Time.deltaTime);
		
		//if (CharController.isGrounded)
		//	isJumping = false;

		
		
	}
	
		void Die()
	{
		print("morreu!");		
		
	}
	
}