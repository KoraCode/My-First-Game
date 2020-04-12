using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;

public class playerController : MonoBehaviour
{                                  
    private Rigidbody2D rb;
    private Animator anim;
    public Collider2D DisColl;
    public Collider2D coll;
    public Transform CellingCheck;
    public AudioSource jumpAudio,hurtAudio,cherryAudio,gemAudio;
    public Joystick joystick;   //手机移动遥杆

    public float speed;
    public float jumpforce;
    public LayerMask ground;
    private int Cherry = 0;
    private int Gem =0;

    public Text CherryNum;
    public Text GemNum;
    private bool isHurt;    //默认是false

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        anim = GetComponent<Animator>();
    }
    void FixedUpdate()      //Update 60帧每秒  FixedUpdate 根据每秒实际帧数平滑帧数
    {
        if (!isHurt)
        {
            Movement();
        }
        SwitchAnim();
    }
    //角色运动
    void Movement()
    {
        float horizontalmove = Input.GetAxis("Horizontal");         //GetAxis是得到一个范围
        float facedircetion = Input.GetAxisRaw("Horizontal");       //GetAxisRaw是得到一个确定的数值 左-1 右1 不移动0
        float crouchtion = Input.GetAxisRaw("Fire1");

        //角色移动
        if(horizontalmove != 0)
        {                                                   //deltaTime 代表两帧之间的间隔时间
            rb.velocity = new Vector2(horizontalmove * speed * Time.fixedDeltaTime, rb.velocity.y);       //2d只有x轴和y轴
            anim.SetFloat("running", Mathf.Abs(facedircetion));
        }
        if(facedircetion!=0)
        {
            transform.localScale = new Vector3(facedircetion, 1, 1);                //Scale有3个轴
        }

        //角色下蹲
        if (!Physics2D.OverlapCircle(CellingCheck.position,0.2f,ground)) {
            if (crouchtion != 0)
            {
                anim.SetBool("crouching", true);
                DisColl.enabled = false;
            }
            else
            {
                anim.SetBool("crouching", false);
                DisColl.enabled = true;
            } 
        }

        //角色跳跃   GetButtonDown只得到一次按下按钮的true信号                                                       
        if (Input.GetButtonDown("Jump") && coll.IsTouchingLayers(ground))        //加的一个判断使它不能空中连跳
        {
            rb.velocity = new Vector2(rb.velocity.x, jumpforce * Time.deltaTime);
            jumpAudio.Play();
            anim.SetBool("jumping", true);
        }
    }
    //切换动画效果
    void SwitchAnim()
    {
        if(rb.velocity.y<0.05f && !coll.IsTouchingLayers(ground))
        {
            anim.SetBool("falling", true);
        }
        if (anim.GetBool("jumping"))    //跳跃判断
        {
            if(rb.velocity.y<0)         //y轴的速度为下降
            {
                anim.SetBool("jumping", false);
                anim.SetBool("falling", true);
            }
        }
        else if(isHurt)         //受伤判断
        {
            anim.SetBool("hurt", true);         //受伤动画与运动停止
            anim.SetFloat("running", 0);
            if (Mathf.Abs(rb.velocity.x)<0.1f)  //反弹的速度降到某位置，受伤动画结束恢复移动
            {
                anim.SetBool("hurt", false);
                anim.SetBool("idle", true);
                isHurt = false;
            }
        }
        else if (coll.IsTouchingLayers(ground))     //下落判断
        {
            anim.SetBool("falling", false);
        }
    }
    //碰撞触发器
    private void OnTriggerEnter2D(Collider2D collision)     //为物品创建一个触发器Trigger
    {
        //收集物品
        if (collision.tag=="Collection")        //碰撞返回的标签为所对应的
        {
            cherryAudio.Play();
            Destroy(collision.gameObject);
            Cherry += 1;
            CherrNum.text = Cherry.ToString();
        }

        if (collision.tag == "Collection1")
        {
            gemAudio.Play();
            Destroy(collision.gameObject);
            Gem += 1;
            GemNum.text = Gem.ToString();
        }

        if (collision.tag == "DeathLine")       //死亡范围
        {
            GetComponent<AudioSource>().enabled = false;
            Invoke("Restart", 2f);  //延时触发方法
        }
    }

    //消灭敌人
    private void OnCollisionEnter2D(Collision2D collision)  //为敌人创建刚体和碰撞体
    {
        if (collision.gameObject.tag == "Enemy")        //如果发生碰撞的物体的标签为Enemy
        {
            Enemy enemy = collision.gameObject.GetComponent<Enemy>();          //创建碰撞体的敌人类的对象
            if (anim.GetBool("falling"))                //在落下动作就是消灭敌人
            {
                enemy.JumpOn();     //调用敌人被消灭后的结果
                rb.velocity = new Vector2(rb.velocity.x, jumpforce * Time.deltaTime);
                anim.SetBool("jumping", true);
            }
            else if(transform.position.x < collision.gameObject.transform.position.x)   //在敌人左边
            {
                rb.velocity = new Vector2(-5, rb.velocity.y);
                hurtAudio.Play();
                isHurt = true;      //更新受伤状态
            }
            else if (transform.position.x > collision.gameObject.transform.position.x)  //在敌人右边
            {
                rb.velocity = new Vector2(5, rb.velocity.y);
                hurtAudio.Play();
                isHurt = true;
            }
        }
    }

    private void Restart()
    {
         SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
}
