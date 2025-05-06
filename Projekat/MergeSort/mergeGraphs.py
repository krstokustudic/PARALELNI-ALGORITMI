import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

#Učitaj podatke iz CSV fajla
df = pd.read_csv("MergeSortResults.csv", sep=";")

sns.set(style="whitegrid")

# -------- 1. Vrijeme izvršavanja --------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="seq_time", label="Sekvencijalno", marker="o")
sns.lineplot(data=df, x="n", y="par_time", hue="threads", marker="o", palette="tab10")
plt.title("Vrijeme izvršavanja (sekvencijalno vs paralelno)")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Vrijeme (s)")
plt.legend(title="Broj tredova")
plt.tight_layout()
plt.show()

# -------- 2. Speedup --------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="speedup", hue="threads", marker="o", palette="tab10")
plt.title("Speedup paralelne verzije")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Speedup")
plt.legend(title="Broj tredova")
plt.tight_layout()
plt.show()

# -------- 3. Efikasnost --------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="efficiency", hue="threads", marker="o", palette="tab10")
plt.title("Efikasnost paralelizacije")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Efikasnost")
plt.legend(title="Broj tredova")
plt.tight_layout()
plt.show()
