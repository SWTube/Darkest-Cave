/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */
#pragma once

#ifdef __WIN32__
import ActionNode;
import BehaviorTreeNode;
import CompositeNode;
import RootNode;
import Sequencer;
import Selector;
import IfDecorator;
import WhileDecorator;
import RepeatDecorator;
import RandomNode;
#else
#include "BehaviorTree/BehaviorTreeNode.h"
#include "BehaviorTree/CompositeNode.h"
#include "BehaviorTree/RootNode.h"
#include "BehaviorTree/ActionNode.h"
#include "BehaviorTree/Sequencer.h"
#include "BehaviorTree/Selector.h"
#include "BehaviorTree/Decorator.h"
#include "BehaviorTree/IfDecorator.h"
#include "BehaviorTree/WhileDecorator.h"
#include "BehaviorTree/RepeatDecorator.h"
#include "BehaviorTree/RandomNode.h"
#endif