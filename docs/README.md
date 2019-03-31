# Welcome!
I am [Josep Lleal Sirvent](https://www.linkedin.com/in/josep-lleal-sirvent/), student of the
[Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). 
This content is generated for the second year’s subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

  - Github account: [Josep Lleal](https://github.com/JosepLleal)
  
I understand that if you are reading this is because you are interested in this topic, one of the cores of the [MMORPGs](https://en.wikipedia.org/wiki/Massively_multiplayer_online_role-playing_game) genre. Before I start explaining how to implement a Buff Manager with C++, it is essential to clearly understand how do Buffs work and to know all the different existing types. So, with this being said, lets start:
  
# What is a Buff? 
Before explaining what a Buff really is, I want to introduce the therm **status effect**:

"A **status effect** is a modification to a game character’s original set of stats that usually comes into play when special powers and abilities are used. The term **status effect** can be applied both to changes that provide a character an advantage (increased attributes, defensive barriers, regeneration), and those that hinder the character (decreased attributes, incapability, degeneration)." *Wikipedia*

With this definition we can clearly distinguish two types of status effects, the ones that provide an **advantage** and the others that provide a **disadvantage**:

- **Buff:** is the status effect that affects an entity in a positive way, providing him an advantage. One of the most used buffs in video games is the health potion, which increases the current health of a character.    

<p align="center">
  <img  src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/healing.gif" width="480" height="300">
</p>
<p align="center">
  <i>Healing in Apex Legends</i>
</p>

- **Debuff:** is the status effect that affects an entity in a negative way, providing him a disadvantage. For instance, a commonly used debuff in video games is the poison, which decreases the current health  of a character. 

<p align="center">
  <img  src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/poison.gif" width="480" height="300">
</p>
<p align="center">
  <i>Poison affecting Apex Legends players</i>
</p>

# Types of effects
When talking about types of effects the most commonly classification is dividing them into two main groups: buffs and debuffs, as I stated before, but indeed, we can organize them in different ways depending on how we approach them. For instance, the classification of buffs and debuffs is approached by looking **how an effect affects an entity**. The other approaches are looking the **durability of an effect** and **how an effect is applied**(referring to the mathematical method used).

## Durability of an effect
When looking at the durability of an effect we can classify them in four groups: **temporary**, **per tick**, **permanent** and **conditional** effects.

- **Temporary effects**: as the name suggests, this type of effect only remains for a specific amount of time, this means that when the effect is finished all the upgraded attributes will be reverted to its original values. For instance, Janna (a champion from [*League of Legends*](https://eune.leagueoflegends.com/en/game-info/)) has an ability called *Eye of the Storm* that shields the target allied champion or herself for 5 seconds and also gaining bonus attack damage.
<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/jannashield.gif" width="480">
</p>
<p align="center">
  <i> Janna Eye of the Storm ability </i>
</p>

- **Per tick effects**: this type of effect could be categorized as a subgroup of temporary effects since they last for a limited amount of time, however, per tick effects have a distinctive feature as the attributes are upgraded, usually, every second. In addition, the upgraded stats will not be reverted once the effect finishes. Per tick effects are mainly used for potions and poisons, for example: [health potions](https://leagueoflegends.fandom.com/wiki/Health_Potion) from *League of Legends* which regenerates 5 health every half-second for 15 seconds, restoring a total of 150 health.
<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/potion.gif" width="480">
</p>
<p align="center">
  <i> Health potion healing League of Legends champion</i>
</p>

- **Permanent effects**: unlike temporary effects, permanent effects will always be active, however, in some games this type of effect is removed when the entity dies. For instance, there are multiple champions in *League of Legends* that have a permanent buff called [*passive*](https://leagueoflegends.fandom.com/wiki/Passive).
<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/nasus_passive.png" width="480">
</p>
<p align="center">
  <i> <a href="https://leagueoflegends.fandom.com/wiki/Nasus">Nasus</a> passive </i>
</p>

- **Conditional effects**: this type of effect could be categorized as a subgroup of permanent effects as their active time is not limited by any timer. A conditional effect has a condition associated with it and while this condition is fulfilled, the buff will be active. For instance, [Garen](https://leagueoflegends.fandom.com/wiki/Garen)'s passive: Garen passively regenerates 0.2/0.8% (based on level) of his maximum health every half-second and is doubled while below 25/50% of health (based on level) of his maximum health. However, this buff is interrupted for 9/4 seconds (based on level) if he takes non-minion damage or if he is hit by an enemy ability (for this effect, the condition associated to it will be the following: *if Garen hasn't been atacked for 9 or 4 seconds (depending on level)*).

<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/GarenP.gif" width="480">
</p>
<p align="center">
  <i> Garen's passive </i>
</p>
<p align="center">
  <i> Notice that in this case Garen's passive is a mixture of a per tick and conditional effect </i>
</p>

## Method used
If we approach effects looking how these are applied mathematically to the stats of an entity, we can classify them in three types: Effect applied **by adding**, **by multiplying** and **by adding a percentage**.

- **By adding**: this type of effect adds or substracts (depending if it is a buff or a debuff) an specific amount to an attribute.  
- **By multiplying**:this type of effect multiplies or divides (depending if it is a buff or a debuff) an specific amount to an attribute.
- **By adding a percentage**: this type of effect adds or substracts (depending if it is a buff or a debuff) a determined percentage of the attribute to upgrade. 

# Buff Manager implementation
Well, now that the topic has been properly introduced, let’s head to a very simple implementation of a **Buff manager**. Our goal is simple, create effects with XML, read and pass them into code and apply them correctly.

## Creation of effects
The first step to do in order to create effects is to create an **structure** containing all the data that an effect will need: 

<p align="center">
  <img src="https://raw.githubusercontent.com/JosepLleal/Research_Buff_Manager/master/docs/images/effect_structure.png">
</p>
