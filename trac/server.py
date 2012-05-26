import web
import trac.controller.wiki as tcw
import trac.controller.ticket as tct
# import trac.controller.login as tcl
import markdown

# web.config.debug = False

urls = (
    '/', 'Index',
    '/login', 'Login',
    '/logout', 'Logout',
    '/wiki', tcw.Index,
    '/wiki/new', tcw.New,
    '/wiki/edit/(\d+)', tcw.Edit,
    '/wiki/delete/(\d+)', tcw.Delete,
    '/wiki/(.*)', tcw.Page,
    '/ticket', tct.Index,
    '/ticket/new', tct.New,
    '/ticket/edit/(\d+)', tct.Edit,
    '/ticket/delete/(\d+)', tct.Delete,
    '/ticket/(.*)', tct.Ticket,
)

app = web.application(urls, globals())

allowed = [('chenyu', '123123')]

if web.config.get('_session') is None:
    session = web.session.Session(
        app,
        web.session.DiskStore('sessions'),
        initializer={'login': 0}
    )
    web.config._session = session
else:
    session = web.config._session

def session_hook():
    web.ctx.session = session

app.add_processor(web.loadhook(session_hook))

class Index:
    def GET(self):
        if session.login:
            raise web.seeother('/wiki')
        else:
            raise web.seeother('/login')

t_globals = {
    'datestr': web.datestr,
    'markdown': markdown.markdown,
    'context': session
}

render = web.template.render(
    'templates/login',
    base='base',
    globals=t_globals
)

class Login:
    form = web.form.Form(
        web.form.Textbox('username', web.form.notnull,
            size=30,
            description="User name:"),
        web.form.Password('password', web.form.notnull,
            size=30,
            description="Password:"),
        web.form.Button('Login'),
    )
    def GET(self):
        if session.login:
            raise web.seeother('/wiki')
        return render.login(self.form)
    def POST(self):
        form = self.form()
        if not form.validates():
            return render.Login(form)
        print form.d.username
        if (form.d.username, form.d.password) in allowed:
            session.login = 1
            session.username = form.d.username
            raise web.seeother('/wiki')
        else:
            raise web.seeother('/login')
        
class Logout:
    def GET(self):
        if session.login:
            session.kill()
        raise web.seeother('/login')

if __name__ == '__main__':
    app.run()
