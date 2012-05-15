import trac.model.wiki as tmw
from trac.config import render
import web

class Index:
    def GET(self):
        pages = tmw.get_pages()
        return render.index(pages)

class Page:
    def GET(self, url):
        page = tmw.get_page_by_url(url)
        if not page:
            raise web.seeother('/new?url=%s' % web.websafe(url))
        return render.view(page)

class New:
    def not_page_exists(url):
        return not bool(tmw.get_page_by_url(url))

    page_exists_validator = web.form.Validator(
        'Page already exists', not_page_exists)

    form = web.form.Form(
        web.form.Textbox('url', web.form.notnull, page_exists_validator,
            size=30,
            description="Location:"),
        web.form.Textbox('title', web.form.notnull, 
            size=30,
            description="Page title:"),
        web.form.Textarea('content', web.form.notnull, 
            rows=30, cols=80,
            description="Page content:", post="Use markdown syntax"),
        web.form.Button('Create page'),
    )

    def GET(self):
        url = web.input(url='').url
        form = self.form()
        form.fill({'url': url})
        return render.new(form)

    def POST(self):
        form = self.form()
        if not form.validates():
            return render.new(form)
        tmw.new_page(form.d.url, form.d.title, form.d.content)
        raise web.seeother('/' + form.d.url)

class Delete:
    def POST(self, id):
        tmw.del_page(int(id))
        raise web.seeother('/')

class Edit:

    form = web.form.Form(
        web.form.Textbox('url', web.form.notnull, 
            size=30,
            description="Location:"),
        web.form.Textbox('title', web.form.notnull, 
            size=30,
            description="Page title:"),
        web.form.Textarea('content', web.form.notnull, 
            rows=30, cols=80,
            description="Page content:", post="Use markdown syntax"),
        web.form.Button('Update page'),
    )

    def GET(self, id):
        page = tmw.get_page_by_id(int(id))
        form = self.form()
        form.fill(page)
        return render.edit(page, form)


    def POST(self, id):
        form = self.form()
        page = tmw.get_page_by_id(int(id))
        if not form.validates():
            return render.edit(page, form)
        tmw.update_page(int(id), form.d.url, form.d.title, form.d.content)
        raise web.seeother('/')
