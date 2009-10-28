# A custom Drupal 6 package

## Features

*	Most useful contribute modules.
*	Drush & custom Drush commands.
*	Contribute themes: ninesixty.
*	Custom install profiles.

## Install

1.	Point your web root to the "html" folder of this project.
1.	Install as usual.

## Setup Drush and use it

1.	Link "drush/drush" to your $PATH or create an alias (refer to "drush/README.txt").
1.	Install Drupal.
1.	Locate to "html" folder with your command line.
1.	Run "drush" to list all available commands.
1.	This package includes a drush command allows you to upgrade code of all contribute modules without installing them. Just run "drush update allcode" and follow the instructions.

## Create a new project

1.	You can fork or clone this project, or just copy things you want.
1.	Normally you want to remove Drush from other projects (keep it with your central/basic drupal project is enough). To do so, remove "drush" and "modules/drush_commands" folder.
1.	You can build your install profile (read next section). In order to make it available to Drupal, put it in "html/profiles" folder or link it there.

## Build a new install profile

**Using "wiredcraft" profile as a basis to modify.**

1.	Copy "profiles/wiredcraft" folder and name it your [profile\_name], and rename the file "wiredcraft.profile" to [profile\_name].profile.
1.	Link your profile folder in to "html/profiles".
1.	Modify the profile (please read comments).
1.	Remove "wiredcraft" profile and its link.
