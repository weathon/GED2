import pandas as pd, pylab
df = pd.read_csv("res.csv")
pylab.plot(df["r"],df["VTree Time"], label="VTree")
pylab.plot(df["r"],df["Baseline Time"], label="Baseline")
pylab.legend()
pylab.show()