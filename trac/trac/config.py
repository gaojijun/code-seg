import web
import markdown

t_globals = {
    'datestr': web.datestr,
    'markdown': markdown.markdown,
}

render = web.template.render(
    'templates',
    base='base',
    globals=t_globals
)
