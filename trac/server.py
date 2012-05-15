import web
import trac.controller.wiki as tcw
import trac.controller.ticket as tct
import markdown


urls = (
    '/wiki', tcw.Index,
    '/wiki/new', tcw.New,
    '/wiki/edit/(\d+)', tcw.Edit,
    '/wiki/delete/(\d+)', tcw.Delete,
    '/wiki/(.*)', tcw.Page,
    '/ticket', tct.Index,
    '/ticket/new', tct.New,
    '/ticket/edit/(\d+)', tct.Edit,
    '/ticket/delete/(\d+)', tct.Delete,
    '/ticket/(.*)', tct.Page,
)

t_globals = {
    'datestr': web.datestr,
    'markdown': markdown.markdown,
}

app = web.application(urls, globals())

if __name__ == '__main__':
    app.run()
