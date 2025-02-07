using UWSR.Models;

namespace UWSR
{
    public static class Security
    {
        // Проверка на владельца комментария
        public static bool CheckIsCommentUser(HttpContext context, Comment comment)
        {
            var currentMode = context.Session.GetString("Mode");
            var currentSessionId = context.Session.Id;

            // Гость может редактировать или удалять только свои комментарии, созданные в текущей сессии
            if (currentMode == "Guest" && comment.SessionId == currentSessionId && comment.Mode == "Guest")
            {
                return true;
            }

            // Владелец может редактировать или удалять любые комментарии
            if (currentMode == "Owner")
            {
                return true;
            }
            return false;
        }




        public static bool CheckIsOwner(HttpContext context)
        {
            var mode = context.Session.GetString("Mode");
            return mode == "Owner";
        }

        public static bool CheckIsGuest(HttpContext context)
        {
            var mode = context.Session.GetString("Mode");
            return mode == "Guest";
        }
    }

}
