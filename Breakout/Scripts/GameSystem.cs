using UnityEngine;
using UnityEngine.SceneManagement;

public class GameSystem : Monobehaviour
{
    public void StartGame()
    {
        SceneManager.LoadScene("MainScene");
    }
}
