import trac.model.ticket as tmt
import web
import markdown

t_globals = {
    'datestr': web.datestr,
    'markdown': markdown.markdown,
}

render = web.template.render(
    'templates/ticket',
    base='base',
    globals=t_globals
)

class Index:
    def GET(self):
        pages = tmt.get_pages()
        return render.index(pages)

class Page:
    def GET(self, url):
        page = tmt.get_page_by_url(url)
        if not page:
            raise web.seeother('/new?url=%s' % web.websafe(url))
        return render.view(page)

class New:
    def not_page_exists(url):
        return not bool(tmt.get_page_by_url(url))

    page_exists_validator = web.form.Validator(
        'Page already exists', not_page_exists)

    form = web.form.Form(
        web.form.Textbox('summary', web.form.notnull,
            size=30,
            description="Summary:"),
        web.form.Textbox('reporter', web.form.notnull,
            size=30,
            description="Reporter:"),
        web.form.Textarea('description', web.form.notnull, 
            rows=15, cols=80,
            description="Description:", post="Use <a href='http://en.wikipedia.org/wiki/Markdown'>markdown</a> syntax"),
        web.form.Dropdown('type',
            args = ['task', 'feature', 'defect', 'enhancement'],
            value = 'feature',
            description="Type:"),
        web.form.Dropdown('priority',
            args = ['blocker', 'critical', 'major', 'minor', 'trivial'],
            value = 'major',
            description="Priority:"),
        web.form.Textbox('start', web.form.notnull,
            size=30,
            description="Start(YYYY/MM/DD):"),
        web.form.Textbox('end', web.form.notnull,
            size=30,
            description="End(YYYY/MM/DD):"),
        web.form.Textbox('assignee',
            size=30,
            description="Assign to:"),

        web.form.Button('Create ticket'),
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
        tmt.new_page(form.d.url, form.d.title, form.d.content)
        raise web.seeother('/wiki/' + form.d.url)

class Delete:
    def POST(self, id):
        tmt.del_page(int(id))
        raise web.seeother('/wiki/')

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
            description="Page content:", post="Use <a href='http://en.wikipedia.org/wiki/Markdown'>markdown</a> syntax"),
        web.form.Button('Update page'),
    )

    def GET(self, id):
        page = tmt.get_page_by_id(int(id))
        form = self.form()
        form.fill(page)
        return render.edit(page, form)


    def POST(self, id):
        form = self.form()
        page = tmt.get_page_by_id(int(id))
        if not form.validates():
            return render.edit(page, form)
        tmt.update_page(int(id), form.d.url, form.d.title, form.d.content)
        raise web.seeother('/')

