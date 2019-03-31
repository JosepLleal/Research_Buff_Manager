# Welcome!
I am [Josep Lleal Sirvent](https://www.linkedin.com/in/josep-lleal-sirvent/), student of the
[Bachelor’s Degree in Video Games by UPC at CITM](https://www.citm.upc.edu/ing/estudis/graus-videojocs/). 
This content is generated for the second year’s subject Project 2, under supervision of lecturer
[Ricard Pillosu](https://es.linkedin.com/in/ricardpillosu).

  - Github account: [Josep Lleal](https://github.com/JosepLleal)
  
I understand that if you are reading this is because you are interested in this topic, one of the cores of the [MMORPGs](https://en.wikipedia.org/wiki/Massively_multiplayer_online_role-playing_game) genre. Before I start explaining how to implement a Buff Manager, it is essential to clearly understand how do Buffs work and to know all the different existing types. So, with this being said, lets start:
  
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
When looking at the durability of an effect we can classify them in three groups: **temporary**, **permanent** and **conditional** effects.

- **Temporary effects**: as the name suggests, this type of effect only remains for a specific amount of time, this means that when the effect is finished all the upgraded attributes will be reverted to its original values. 
- **Per tick effects**: this type of effect could be categorized as a subgroup of temporary effects since they last for a limited amount of time, however, per tick effects have a distinctive feature as the attributes are upgraded, usually, every second. In addition, the upgraded stats will not be reverted once the effect finishes. Per tick effects are mainly used for potions and poisons, for example: [health potions](https://leagueoflegends.fandom.com/wiki/Health_Potion) from [*League of Legends*](https://eune.leagueoflegends.com/en/game-info/) which regenerates 5 health every half-second for 15 seconds, restoring a total of 150 health.
- **Permanent effects**: unlike temporary effects, permanent effects will always be active as long as the entity remains alive.  
- **Conditional effects**:

## Method used
- **By adding**:
- **By multiplying**:
- **By percentage**:

