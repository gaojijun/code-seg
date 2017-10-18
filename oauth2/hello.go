// Refer to https://jacobmartins.com/2016/02/29/getting-started-with-oauth2-in-go/

package hello

import (
    "fmt"
    "io/ioutil"
    "net/http"

    "golang.org/x/oauth2"
    "golang.org/x/oauth2/google"
    "google.golang.org/appengine"
    "google.golang.org/appengine/urlfetch"
)

var (
	googleOauthConfig = &oauth2.Config{
		RedirectURL: "https://auth2-test-183206.appspot.com/GoogleCallback",
		ClientID: "client ID", // TODO: modify this and secret
		ClientSecret: "client secret",
		Scopes: []string{
			"https://www.googleapis.com/auth/userinfo.profile",
			"https://www.googleapis.com/auth/userinfo.email",
		},
		Endpoint: google.Endpoint,
	}
	oauthStateString = "random"
)

func init() {
    http.HandleFunc("/", handler)
    http.HandleFunc("/GoogleLogin", handleGoogleLogin)
    http.HandleFunc("/GoogleCallback", handleGoogleCallback)
}

const htmlIndex = `<html><body>
<a href="/GoogleLogin">Log in with Google</a>
</body></html>
`

func handler(w http.ResponseWriter, r *http.Request) {
    fmt.Fprint(w, htmlIndex)
}

func handleGoogleLogin(w http.ResponseWriter, r *http.Request) {
    url := googleOauthConfig.AuthCodeURL(oauthStateString)
    http.Redirect(w, r, url, http.StatusTemporaryRedirect)
}

func handleGoogleCallback(w http.ResponseWriter, r *http.Request) {
    state := r.FormValue("state")
    if state != oauthStateString {
        s := fmt.Sprintf("invalid oauth state, expected '%s', got '%s'\n", oauthStateString, state)
        fmt.Fprint(w, s)
	return
    }

    code := r.FormValue("code")
    ctx := appengine.NewContext(r)
    token, err := googleOauthConfig.Exchange(ctx, code)
    if err != nil {
        s := fmt.Sprintf("Code exchange failed with '%s'\n", err)
        fmt.Fprint(w, s)
	return
    }
    client := urlfetch.Client(ctx)
            response, err := client.Get("https://www.googleapis.com/oauth2/v2/userinfo?access_token=" + token.AccessToken)

    if err != nil {
        s := fmt.Sprintf("Get user info error '%s'\n", err)
        fmt.Fprint(w, s)
	return
    }

    defer response.Body.Close()
    contents, err := ioutil.ReadAll(response.Body)
    if err != nil {
        s := fmt.Sprintf("Code exchange failed with '%s'\n", err)
        fmt.Fprint(w, s)
	return
    }
    fmt.Fprintf(w, "Content: %s\n", contents)

}
