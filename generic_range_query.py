
from random import randrange as rand
from random import sample
from ctypes import windll
from pathlib import Path

import tkinter as tk
from tkinter.font import Font
from tkinter.messagebox import showinfo

windll.shcore.SetProcessDpiAwareness(True) #No Blurry Text
window = tk.Tk()
window.title("某Return 3rd教學做出來的簡單測資生成器")
window.resizable(width=False, height=False)
#window.geometry("1000x750")

###############

abort = False
gen_var, params = [], dict()
gen_key = [
    "n", "q", "ext", 
    "pre", "post",
    "rpt"
]
default_values = {
    "n":0, "q":0, "ext":[0, 2**31-1],
    "pre":None, "post":None,
    "rpt":1
}
use_default = dict((s, False) for s in gen_key)
instr = [
    ["陣列長度(建議≤10⁷) N", "1000"], ["查詢數量(建議≤10⁷) Q", "1000"], 

    ["陣列內數字範圍 ext", "0:2^31-1"], ["查詢區間前生成數字 pre", "0:1000"],
    ["查詢區間後生成數字 post", "0:1000"], [],

    ["生成測資數 tst", "1"], ["輸出文件格式 fmt", "output##.txt"],
    ["輸出編號從幾開始? idx", "0"], []
]
instr_sub = [
    "(=0只生成查詢，範圍為ext)", "(=0只生成陣列)",

    "(預設為0~(2^31)-1)", '(以";"分隔可生成多個數字)',
    '(以";"分隔可生成多個數字)', "",

    '(請勿使用區間字元":")','("#"為測資編號)',
    "", ""
]

###############

def popup_error(msg):
    showinfo("Error", msg)

def rng(param):
    if isinstance(param, list): 
        if len(param) == 1: 
            return param[0]
        if param[0] > param[1]: 
            param[0], param[1] = param[1], param[0]
        return rand(param[0], param[1]+1)
    return param

def evaluate(evt_str):
    global abort
    if abort: return
    #recur to return a list
    if ':' in evt_str: return [evaluate(i) for i in evt_str.split(':')]

    #single value evaluation
    evt_str = evt_str.replace("^","**").replace("/","//")
    try: 
        evt_str = eval(evt_str, {'__builtins__': None})
    except: 
        popup_error("非法的參數格式!")
        abort = True
        return

    return int(evt_str)
    

def ev_format(key, evt_str):
    if not evt_str:
        use_default[key] = True
        return key, default_values[key]

    safety = {'0','1','2','3','4','5','6','7','8','9',
              'e',' ','.',':',';','+','-','*','/','^','(',')'}

    if any(c not in safety for c in evt_str):
        popup_error("非法的參數格式!")
        global abort
        abort = True
        return None, None
    if ';' in evt_str:
        return key, [evaluate(i) for i in evt_str.split(';')]
    else:
        return key, evaluate(evt_str)

def gen(gen_var = gen_var):
    idx = gen_var[-1].get()
    s = gen_var[-2].get()
    if not idx: idx = 0
    if not s: s = "output##.txt"
    idx = int(idx)
    s = [s]
    s.append(s[0].count("#"))

    #n, q, ext, qry_sz, pre, post, rpt
    #debug: 
    print([ev_format(k,v) for (k,v) in zip(gen_key, [e.get() for e in gen_var[:-2]])])
    params = dict([ev_format(k,v) for (k,v) in zip(gen_key, [e.get() for e in gen_var[:-2]])])
    if abort: return

    #Generate
    Path("generated").mkdir(parents=True, exist_ok=True)
    for i in range(params["rpt"]):
        f = open("generated/"+
                 s[0].replace("#"*s[1], str(idx).zfill(s[1])), 'w+')

        #N, Q, array
        Q = rng(params['q'])
        if not use_default['n']: 
            print(params['n'], end=' ', file=f)
        if not use_default['q']: 
            print(Q, end=' ', file=f)
        if not (use_default['n'] and use_default['q']): 
            print(file=f)
        if not use_default['n']: 
            print(*[rng(params['ext']) for j in range(params['n'])], file=f)

        #more formatting
        for i in ['pre', 'post']:
            if not use_default[i]:
                if isinstance(params[i], int): 
                    params[i] = [params[i]]
                if not (any(isinstance(k, list) for k in params[i])):
                    params[i] = [params[i]]
        #debug: print(*[(k, params[k]) for k in params], sep='\n')

        #queries
        output = [[] for i in range(Q)]
        if not use_default['pre']:
            for i in range(Q):
                for k in params['pre']:
                    output[i].append(rng(k))
                    
        if not use_default['q']:
            if not use_default['n']:
                for i in range(Q):
                    a, b = sample(range(0, params['n']+1), 2)
                    if a > b: a, b = b, a
                    output[i].append(a)
                    output[i].append(b)
            elif not use_default['ext']:
                for i in range(Q):
                    a, b = sample(range(*params['ext']), 2)
                    if a > b: a, b = b, a
                    output[i].append(a)
                    output[i].append(b)

        if not use_default['post']:
            for i in range(Q):
                for k in params['post']:
                    output[i].append(rng(k))

        for line in output:
            print(*line, end='\n', file=f)
        #next loop
        f.close()
        idx += 1
    #finished
    showinfo("成功!", "所有的測資已成功生成!")
    gen_var[-1].delete(0, tk.END)
    gen_var[-1].insert(0, str(idx))
###############


##### Main Structure

lbl_title = tk.Label(
    master = window,
    width = 30,
    text = "A. S. I. R. Q. T. G.",
    font = Font(family="Consolas", size=36, weight="bold")
); lbl_title.grid()
lbl_title = tk.Label(
    master = window,
    text = "(A Simple Integer Range Query Testcase Generator)",
    font = Font(family="Consolas", size=12, weight="bold")
); lbl_title.grid()
lbl_title = tk.Label(
    master = window,
    text = '''注意: 若陣列長度、數字極值的數值極大(如3^3^3^3)，可能導致程式當機
若欲生成的測資較大，可能顯示沒有回應，屬於正常情況，此時請耐心等待''',
    font = Font(family="PMingLiU-ExtB", size=12)
); lbl_title.grid()
lbl_title = tk.Label(
    master = window,
    height = 2,
    text = '*可利用":"字元來表示區間*',
    font = Font(family="PMingLiU-ExtB", size=12)
); lbl_title.grid()

frm_ui = tk.Frame(
    master = window,
    borderwidth = 5
); frm_ui.grid()


##### UI Body
for i in range(len(instr)):
    frm_sub = tk.Frame(
       master = frm_ui,
       borderwidth = 5
    ); frm_sub.grid(row=i//2, column=i&1)
    if not instr[i]: continue


    #Left UI - Descriptions
    frm_ssub = tk.Frame(
        master = frm_sub,
        borderwidth = 5
    ); frm_ssub.grid(row=0, column=0, padx=(20, 0))
    lbl_ssub = tk.Label(
        master = frm_ssub,
        anchor = 'e',
        width = 20,
        #height = 2,
        text = instr[i][0],
        font = Font(family="PMingLiU-ExtB", size=12)
    ); lbl_ssub.grid()
    if instr_sub[i]:
        lbl_ssub = tk.Label(
            master = frm_ssub,
            anchor = 'e',
            width = 25,
            #height = 2,
            text = instr_sub[i],
            font = Font(family="PMingLiU-ExtB", size=10)
        ); lbl_ssub.grid()


    # Right UI - User Inputs
    frm_ssub = tk.Frame(
        master = frm_sub,
        borderwidth = 5 
    ); frm_ssub.grid(row=0, column=1, padx=(10, 20))
    ent_ssub = tk.Entry(
        master = frm_ssub,
        width = 20,
    )
    ent_ssub.insert(0, instr[i][1])
    gen_var.append(ent_ssub)
    ent_ssub.grid()

##### Navigation

frm_gen = tk.Frame(
    master = window,
    borderwidth = 10,
); frm_gen.grid()
btn_gen = tk.Button(
    master = frm_gen,
    width = 20,
    height = 2,
    text = "Generate!",
    font = Font(family="Consolas", size=16, weight="bold"),
    fg = "royalblue",
    bg = "lightgreen",
    command = gen
); btn_gen.grid()

##### Finalize

window.mainloop()