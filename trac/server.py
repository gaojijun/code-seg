import web
import trac.controller.wiki as tcw
import markdown


urls = (
    '/wiki', tcw.Index,
    '/wiki/new', tcw.New,
    '/wiki/edit/(\d+)', tcw.Edit,
    '/wiki/delete/(\d+)', tcw.Delete,
    '/wiki/(.*)', tcw.Page,
)

t_globals = {
    'datestr': web.datestr,
    'markdown': markdown.markdown,
}

app = web.application(urls, globals())

if __name__ == '__main__':
    app.run()
