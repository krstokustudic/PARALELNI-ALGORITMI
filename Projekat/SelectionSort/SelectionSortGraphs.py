import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns


df = pd.read_csv("SelectionSortResults.csv", sep=";")

# Postavi stil
sns.set(style="whitegrid")

# -------- 1. Vrijeme izvršavanja --------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="seq_time", label="Sekvencijalno", marker="o")
sns.lineplot(data=df, x="n", y="par_time", hue="threads", palette="tab10", marker="o")
plt.title("Vrijeme izvršavanja - Selection Sort")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Vrijeme (s)")
plt.legend(title="Broj thread-ova")
plt.tight_layout()
plt.show()

# -------- 2. Speedup --------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="speedup", hue="threads", marker="o", palette="tab10")
plt.title("Speedup - Selection Sort")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Speedup")
plt.legend(title="Broj thread-ova")
plt.tight_layout()
plt.show()

# -------- 3. Efikasnost --------
plt.figure(figsize=(10, 6))
sns.lineplot(data=df, x="n", y="efficiency", hue="threads", marker="o", palette="tab10")
plt.title("Efikasnost paralelizacije - Selection Sort")
plt.xlabel("Veličina niza (n)")
plt.ylabel("Efikasnost")
plt.legend(title="Broj thread-ova")
plt.tight_layout()
plt.show()
