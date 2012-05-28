import web
import trac.controller.user as tcu
import trac.controller.wiki as tcw
import trac.controller.ticket as tct
import trac.controller.login as tcl

urls = (
    '/', 'Index',

    '/login', tcl.Login,
    '/logout', tcl.Logout,

    '/user', tcu.Index,
    '/user/new', tcu.New,
    '/user/edit/(\d+)', tcu.Edit,
    '/user/delete/(\d+)', tcu.Delete,
    '/user/(.*)', tcu.View,

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

class Index:
    def GET(self):
        if session.login:
            raise web.seeother('/wiki')
        else:
            raise web.seeother('/login')
