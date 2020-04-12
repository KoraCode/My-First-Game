using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;
using UnityEngine.Audio;

public class Menu : MonoBehaviour
{
    public AudioMixer audioMixer;
    public void PlayGame()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().buildIndex + 1);
    }

    public void QuitGame()
    {
        Application.Quit();
    }

    public void UIEnable()
    {
        GameObject.Find("Canvas/MainMenu/UI").SetActive(true);
    }

    public void PauseEnable()
    {
        GameObject.Find("Canvas/Pause/PauseMenu").SetActive(true);
        Time.timeScale = 0;
    }

    public void ResumeEnable()
    {
        GameObject.Find("Canvas/Pause/PauseMenu").SetActive(false);
        Time.timeScale = 1;
    }

    public void SetVolume(float value)
    {
        audioMixer.SetFloat("MainVolume", value);
    }
}
