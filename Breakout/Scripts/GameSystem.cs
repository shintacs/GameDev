using UnityEngine;
using UnityEngine.SceneManagement;

public class GameSystem : Monobehaviour
{
    public void StartGame()
    {
        SceneManager.LoadScene("MainScene");
    }
    
    public void Retry()
    {
        SceneManager.LoadScene(SceneManager.GetActiveScene().name);
    }
    
    public void ReturnHome()
    {
        SceneManager.LoadScene("StartScene");
    }
}
