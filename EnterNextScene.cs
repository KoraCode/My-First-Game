using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class EnterNextScene : MonoBehaviour
{

    void Update()
    {
        if(Input.GetKeyDown(KeyCode.E))
        {
            SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex+1);     //当前场景编号+1
        }
    }
}
