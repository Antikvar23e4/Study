using Microsoft.AspNetCore.Mvc;

namespace ASPCMVC07.Controllers
{
    [Route("it")]
    public class TAResearch : Controller
    {
        [HttpGet]
        [Route("{n:int}/{str}")]
        public string M04(int n, string str)
        {
            // 
            return $"GET:M04:/{n}/{str}";
        }
        
        [HttpGet]
        [HttpPost]
        [Route("{b:bool}/{letters:alpha}")]
        public string M05(bool b, string letters)
        {
            // /it/true/abc
            return $"{Request.Method}:M05:/{b}/{letters}";
        }


        [HttpGet]
        [HttpDelete]
        [Route("{f:float}/{str:maxlength(5):minlength(3)}")]
        public string M06(float f, string str)
        {
            // /it/5.5/abc
            return $"{Request.Method}:M06:/{f}/{str}";
        }


        [HttpPut]
        [Route("{letters:alpha:minlength(3):maxlength(4)}/{n:int:max(200):min(100)}")]
        public string M07(string letters, int n)
        {
            // 
            return $"PUT:M07:/{letters}/{n}/";
        }


        [HttpPost]
        [Route("{mail:regex(^\\S+@\\S+\\.\\S+$)}")]
        public string M08(string mail)
        {
            // 
            return $"POST:M08/{mail}";
        }
    }
}
